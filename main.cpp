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

#include "camera.h"
#include "config.h"

#include "objectfactory.h"
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
#include "dbmanager.h"
#include "weatherdata.h"
#include "configuration.h"

//Debug logging flag
bool g_debug = false;

QString MY_IP_ADDR;

// this only exists as we cannot copy qobjects
QList <WeatherData*> g_weatherList;
QList <PondData*> g_pondList;

QString homeLocation;
DbManager *g_sqlDb;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("SMAH");
    QCommandLineParser parser;
    QCommandLineOption nogui("nogui", QCoreApplication::translate("main", "Start headless"));
    parser.addOption(nogui);
    QCommandLineOption debug("debug", QCoreApplication::translate("debug", "Debug mode"));
    parser.addOption(debug);
    QCommandLineOption nocursor("nocursor", QCoreApplication::translate("main", "Hide cursor"));
    parser.addOption(nocursor);
    parser.process(a);

    const QStringList args = parser.positionalArguments();

    bool hideGui = parser.isSet(nogui);
    bool hideCursor = parser.isSet(nocursor);
    g_debug = parser.isSet(debug);

    EventFilter filter;
    a.installEventFilter(&filter);
    qInstallMessageHandler(systemlogHandler);
    qInfo() << "SMAH Verion " << BUILD << DATE;

    /* setup paths */
    homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QDir::setCurrent(homeLocation + "/.smah/");

    /* NEW load configs */
    Configuration *configuration = new Configuration();
    configuration->loadBaseConfiguration();
    configuration->loadUserDefinedConfiguration();

    /* Start creating objecrs from config */
    ObjectFactory factory;
    factory.createCameraObjects(configuration);
    factory.createShellyObjects(configuration);
    factory.createZoneObjects(configuration);
    factory.createSensorObjects(configuration);
    factory.createLightObjects(configuration);
    factory.createPresetObjects(configuration);
    factory.createSceneObjects(configuration);

    /* open zwave websocket */
    ZWaveSocket *zWaveSock = new ZWaveSocket(QUrl("ws://10.3.10.2:3000"), true , factory.getSensorObjects());
    zWaveSock->setObjectName("sock");

    /* Prepare the database now */
    g_sqlDb = new DbManager("smah.db");
    g_sqlDb->createTable();

    // determine our IP addy
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    for(int nIter=0; nIter<list.count(); nIter++)
    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                MY_IP_ADDR = list[nIter].toString();
    }


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
        //if (g_debug)
            //qDebug() << request;
        weatherdata->setHumidity(request.query().queryItemValue("humidity").toInt());
        weatherdata->setTemperature(request.query().queryItemValue("tempf").toFloat());
        weatherdata->setWindSpeed(request.query().queryItemValue("windspeedmph").toFloat());
        weatherdata->setWindMaxGust(request.query().queryItemValue("maxdailygust").toFloat());
        weatherdata->setUV(request.query().queryItemValue("uv").toInt());
        return "OK";
    });
    httpServer.route("/pond?", [ponddata](const QHttpServerRequest &request) {
        if (g_debug)
            qDebug() << request;
        ponddata->setPH(request.query().queryItemValue("ph_v").toFloat());
        ponddata->setTemperature(request.query().queryItemValue("temp_v").toFloat());
        return "OK";
    });
    auto tcpserver = std::make_unique<QTcpServer>();
    if (!tcpserver->listen(QHostAddress::Any,8888) || !httpServer.bind(tcpserver.get())) {
        qFatal() << "Server failed to listen on a port.";
    } else {
        qInfo() << "HTTP Weather listener on port" << tcpserver->serverPort();
    }




    //loadActions();
    //loadScenes();

    // headless mode, since qml won't even work without a screen attached
    // setup QML bits
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
    qmlRegisterType<Shelly>("smah.shellyrgbw", 1, 0, "ShellyRGBW");
    qmlRegisterType<WeatherData>("smah.weatherdata", 1, 0, "WeatherData");
    qmlRegisterType<PondData>("smah.ponddata", 1, 0, "PondData");
    qmlRegisterType<DbManager>("smah.dbmanager", 1, 0, "DbManager");
    qmlRegisterType<Scene>("smah.scene", 1, 0, "Scene");
    qmlRegisterType<Camera>("smah.camera", 1, 0, "Camera");
    qmlRegisterType<Configuration>("smah.configuration", 1, 0, "Configuration");
    qmlRegisterType<Configuration::AmbientLoopConfiguration>("smah.configuration.ambient", 1, 0, "ConfigurationAmbient");
    qmlRegisterType<ObjectFactory>("smah.objectfactory", 1, 0, "ObjectFactory");

    foreach (WeatherData *weatherdata, g_weatherList)
    {
        qmlWeatherData.append(QVariant::fromValue(weatherdata));
    }
    foreach (PondData *ponddata, g_pondList)
    {
        qmlPondData.append(QVariant::fromValue(ponddata));
    }

    if (!hideGui) {
        ImageProvider *imageProvider = new ImageProvider(factory.getPresetObjects());
        engine.addImageProvider("images", imageProvider);
        engine.rootContext()->setContextProperty("net_ip", MY_IP_ADDR);
        engine.rootContext()->setContextProperty("b_date", DATE);
        engine.rootContext()->setContextProperty("b_build", BUILD);
        engine.rootContext()->setContextProperty("weatherdataitems", qmlWeatherData);
        engine.rootContext()->setContextProperty("ponddataitems", qmlPondData);
        engine.rootContext()->setContextProperty("db", g_sqlDb);
        engine.rootContext()->setContextProperty("applicationDirPath", QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory));
        engine.rootContext()->setContextProperty("idleDetection", &filter);
        engine.rootContext()->setContextProperty("debug", QVariant(g_debug));
        engine.rootContext()->setContextProperty("factory", &factory);
        engine.rootContext()->setContextProperty("configuration", configuration);

        engine.addImportPath(":/SMAHComponents/");
        engine.addImportPath(":/ZoneComponents/");

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
