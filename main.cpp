#include <QApplication>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QString>
#include <QGuiApplication>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlApplicationEngine>
#include <QtQuick/QQuickWindow>
#include <QHttpServer>
#include <QTcpServer>

#include "config.h"

#include "ponddata.h"
#include "qnetworkreply.h"
#include "zone.h"
//#include "light.h"
//#include "preset.h"
#include "logger.h"
#include "eventfilter.h"
#include "sensor.h"
#include "build_number.h"
#include "imageprovider.h"
#include "zwavesocket.h"
#include "shellyrgbw.h"
#include "dbmanager.h"
#include "weatherdata.h"

QString MY_HW_ADDR;
QString MY_IP_ADDR;
int MY_DEVICE_ID;

extern QMap<QString, Zone*> g_zoneMap;
extern QMap<int, Preset*> g_colorPresetMap;
extern QMap <QString, RPIDevice*> g_deviceList;
extern QMap <QString, ShellyRGBW*> g_shellyList;
extern QList <Sensor*> g_sensorList;
// this only exists as we cannot copy qobjects
QList <WeatherData*> g_weatherList;
QList <PondData*> g_pondList;
//
//QMap <int, Light*> g_lightMap;
//QMap <int, int> g_nodeValues;


//bool zwave_ready = false;
QString homeLocation;
//QString g_zwaveDriver = "0";
DbManager *g_sqlDb;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("SMAH");
    QCommandLineParser parser;
    QCommandLineOption nogui("nogui", QCoreApplication::translate("main", "Start headless"));
    parser.addOption(nogui);
    QCommandLineOption nocursor("nocursor", QCoreApplication::translate("main", "Hide cursor"));
    parser.addOption(nocursor);
    parser.process(a);

    const QStringList args = parser.positionalArguments();

    bool hideGui = parser.isSet(nogui);
    bool hideCursor = parser.isSet(nocursor);


    EventFilter filter;
    a.installEventFilter(&filter);
    qInstallMessageHandler(systemlogHandler);
    qInfo() << "SMAH Verion " << BUILD << DATE;
    // determine our MAC addy
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (
                    interface.name() == "wlp5s0"
                    || interface.name() == "wlan0"
                    || interface.name() == "eth0"
                    || interface.name() == "enp4s0"
                    )
                {
                    MY_HW_ADDR = interface.hardwareAddress();
                    break;
                }
            }
        }
    }

    // determine our IP addy
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++)
    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                MY_IP_ADDR = list[nIter].toString();
    }

    homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);

    // start TCP server for weather stuff
    WeatherData *weatherdata = new WeatherData;
    PondData *ponddata = new PondData;
    g_weatherList.append(weatherdata);
    g_pondList.append(ponddata);
    QHttpServer httpServer;
    httpServer.route("/data/report/", [](const QHttpServerRequest &request) {
        qDebug() << request;
        return "OK";
    });
    httpServer.route("/weather", [weatherdata](const QHttpServerRequest &request) {
        weatherdata->setHumidity(request.query().queryItemValue("humidity").toInt());
        weatherdata->setTemperature(request.query().queryItemValue("tempf").toFloat());
        weatherdata->setWindSpeed(request.query().queryItemValue("windspeedmph").toFloat());
        return "OK";
    });
    httpServer.route("/pond?", [ponddata](const QHttpServerRequest &request) {
        ponddata->setPH(request.query().queryItemValue("ph").toFloat());
        ponddata->setTemperature(request.query().queryItemValue("temp").toFloat());
        qDebug() << request;
        return "OK";
    });
    auto tcpserver = std::make_unique<QTcpServer>();
    if (!tcpserver->listen(QHostAddress::Any,8888) || !httpServer.bind(tcpserver.get())) {
        qFatal() << "Server failed to listen on a port.";
    } else {
        qInfo() << "HTTP Weather listener on port" << tcpserver->serverPort();
    }

    //DatagramHandler broadcaster;

    QDir::setCurrent(homeLocation + "/.smah/");

    ZWaveSocket *zWaveSock = new ZWaveSocket(QUrl("ws://10.1.10.60:3000"), true);
    zWaveSock->setObjectName("sock");
    // Prepare the database now
    g_sqlDb = new DbManager("smah.db");
    g_sqlDb->createTable();

    loadZones();
    loadPresets();
    loadActions();


    // headless mode, since qml won't even work without a screen attached
    // setup QML bits
    QVariantList qmlZones;
    QVariantList qmlPresets;
    QVariantList qmlSensors;
    QVariantList qmlSHellyRGBW;
    QVariantList qmlWeatherData;
    QVariantList qmlPondData;

    QQmlEngine engine;

    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    if (hideCursor)
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    qmlRegisterType<Light>("smah.light", 1, 0, "Light");
    qmlRegisterType<Zone>("smah.zone", 1, 0, "Zone");
    qmlRegisterType<Zone>("smah.preset", 1, 0, "Preset");
    qmlRegisterType<Sensor>("smah.sensor", 1, 0, "Sensor");
    qmlRegisterType<ShellyRGBW>("smah.shellyrgbw", 1, 0, "ShellyRGBW");
    qmlRegisterType<WeatherData>("smah.weatherdata", 1, 0, "WeatherData");
    qmlRegisterType<PondData>("smah.ponddata", 1, 0, "PondData");
    qmlRegisterType<DbManager>("smah.dbmanager", 1, 0, "DbManager");

    foreach (QString key, g_zoneMap.keys())
    {
        qmlZones.append(QVariant::fromValue(g_zoneMap.value(key)));
    }

    foreach (Sensor *key, g_sensorList)
    {
        qmlSensors.append(QVariant::fromValue(key));
    }

    foreach (Preset *preset, g_colorPresetMap)
    {
        qmlPresets.append(QVariant::fromValue(preset));
    }

    foreach (ShellyRGBW *shelly, g_shellyList)
    {
        qmlSHellyRGBW.append(QVariant::fromValue(shelly));
    }
    foreach (WeatherData *weatherdata, g_weatherList)
    {
        qmlWeatherData.append(QVariant::fromValue(weatherdata));
    }
    foreach (PondData *ponddata, g_pondList)
    {
        qmlPondData.append(QVariant::fromValue(ponddata));
    }
    if (!hideGui) {

        QNetworkAccessManager* manager = new QNetworkAccessManager();
        QNetworkRequest request;
        request.setUrl(QUrl("https://api.weather.gov/gridpoints/SEW/107,55/forecast"));
        QNetworkReply *reply = manager->get(request);

        QAbstractSocket::connect(reply, &QNetworkReply::finished, [=]() {

            if(reply->error() == QNetworkReply::NoError)
            {
                QByteArray response = reply->readAll();
                //qDebug() << response;
                // do something with the data...
            }
            else // handle error
            {
                qDebug() << reply->errorString();
            }
        });

        ImageProvider *imageProvider = new ImageProvider;
        engine.addImageProvider("images", imageProvider);
        engine.rootContext()->setContextProperty("sensorList", QVariant::fromValue(qmlSensors));
        engine.rootContext()->setContextProperty("presetList", QVariant::fromValue(qmlPresets));
        engine.rootContext()->setContextProperty("zoneList", QVariant::fromValue(qmlZones));
        engine.rootContext()->setContextProperty("shellyRGBWList", QVariant::fromValue(qmlSHellyRGBW));
        engine.rootContext()->setContextProperty("net_ip", MY_IP_ADDR);
        engine.rootContext()->setContextProperty("net_mac", MY_HW_ADDR);
        engine.rootContext()->setContextProperty("b_date", DATE);
        engine.rootContext()->setContextProperty("b_build", BUILD);
        engine.rootContext()->setContextProperty("weatherdataitems", qmlWeatherData);
        engine.rootContext()->setContextProperty("ponddataitems", qmlPondData);
        engine.rootContext()->setContextProperty("db", g_sqlDb);
        engine.rootContext()->setContextProperty("applicationDirPath", QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory));
        engine.rootContext()->setContextProperty("idleDetection", &filter);
        QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
        component.loadUrl(QUrl(QStringLiteral("qrc:/Main.qml")));
        if (component.isReady()) {
            component.create();
        } else {
            qWarning() << "Can't create main window!" << component.errorString();
        }
    }
    return a.exec();
}
