#include <QApplication>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>
#include <QNetworkInterface>
#include <QHostAddress>

#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlEngine>

#include "zone.h"
#include "light.h"
#include "mainwindow.h"
#include "preset.h"
#include "logger.h"
#include "datagramhandler.h"
#include "pigpio.h"
#include "gpio_defs.h"
#include "tcpconnectionfactory.h"
#include "pca9685.h"
#include "i2c/i2c.h"
#include "eventfilter.h"
#include "sensor.h"

QMap<QString, Zone> gZoneMap;
QMap<int, Preset> gColorPresetMap;
QList<ClientSocket*> g_clientMap;
QMap <QString, RPIDevice*> g_deviceList;
QList <Sensor*> g_sensorList;
QMap <int, Light*> g_lightMap;
QMap <int, int> g_nodeValues;
QString MY_HW_ADDR;
QString MY_IP_ADDR;
bool zwave_ready = false;
bool g_PCA9685_ready = false;
smah_i2c bus;
QString homeLocation;
uint32 g_homeId = -32767;
QString g_zwaveDriver = "0";

TCPConnectionFactory tcpServer;
int MY_DEVICE_ID;

void loadZones()
{
    QDomDocument zoneXMLDocument;
    QFile zoneXMLFile("smah_zones.xml");

    if (!zoneXMLDocument.setContent(&zoneXMLFile)) {
        qCritical() << "Failed to load zones";
        return;
    }

    zoneXMLFile.close();

    QDomElement root = zoneXMLDocument.firstChildElement();
    QDomNodeList zoneItems = root.elementsByTagName("zone");
    /* enumrate zones */
    for (int i = 0; i < zoneItems.count(); i++) {
        QDomNode itemnode = zoneItems.at(i);
        if (itemnode.isElement()) {
            QDomElement element = itemnode.toElement();

            Zone zone(
                        element.attribute("id").toInt(),
                        element.attribute("name")
                        );
            /* each rpi device in the zone */
            QDomNodeList devices = element.elementsByTagName("device");
            for (int a = 0; a < devices.count(); a++) {
                QDomNode deviceNode = devices.at(a);
                if (deviceNode.isElement()) {
                    QDomElement powerElement = deviceNode.toElement();
                    RPIDevice *rpidevice = new RPIDevice(
                                powerElement.attribute("id").toInt(),
                                powerElement.attribute("name"),
                                powerElement.attribute("hw")
                                );
                    zone.addDevice(rpidevice);
                    g_deviceList.insert(powerElement.attribute("hw"),rpidevice);
                    if (rpidevice->getHwAddress() == MY_HW_ADDR)
                        /* probably unused now from home_id */
                        MY_DEVICE_ID = rpidevice->getId();
                    //zone->powerControls.insert(powerElement.attribute("id").toInt(), powerElement.attribute("name"));
                }
            }
            /* each light in the zone */
            QDomNodeList lightItems = element.elementsByTagName("light");
            for (int a = 0; a < lightItems.count(); a++) {
                QDomNode lightNode = lightItems.at(a);
                if (lightNode.isElement()) {
                    QDomElement lightElement = lightNode.toElement();
                    bool ok;
                    Light *light = new Light(lightElement.attribute("id").toInt(),
                                             lightElement.attribute("name"),
                                             lightElement.attribute("type").toInt(),
                                             lightElement.attribute("device").toInt(),
                                             lightElement.attribute("bank").toShort(),
                                             lightElement.attribute("home_id").toUInt(&ok, 16)
                                             );
                    zone.addLight(light);
                    g_lightMap.insert(lightElement.attribute("id").toInt(), light);
                }
            }

            /* each sensor device in the zone */
            QDomNodeList sensors = element.elementsByTagName("sensor");
            for (int a = 0; a < sensors.count(); a++) {
                QDomNode sensorNode = sensors.at(a);
                if (sensorNode.isElement()) {
                    QDomElement sensorElement = sensorNode.toElement();
                    bool ok;
                    Sensor *sensor = new Sensor(
                                sensorElement.attribute("name"),
                                sensorElement.attribute("id").toShort(),
                                sensorElement.attribute("device").toInt(),
                                sensorElement.attribute("farenheit").toShort(),
                                sensorElement.attribute("home_id").toUInt(&ok, 16)
                                );
                    zone.addSensor(sensor);
                    g_sensorList.append(sensor);


                }
            }
            gZoneMap.insert(zone.getName(),zone);
        }
    }
}

void loadPresets()
{
    QDomDocument zoneXMLDocument;
    QFile zoneXMLFile("light_presets.xml");

    if (!zoneXMLDocument.setContent(&zoneXMLFile)) {
        qCritical() << "Failed to load presets";
        return;
    }

    zoneXMLFile.close();

    short presetID = 0;
    QDomElement root = zoneXMLDocument.firstChildElement();

    QDomNodeList staticItems = root.elementsByTagName("static");
    QDomNodeList dynamicItems = root.elementsByTagName("dynamic");

    //load static presets
    for (int i = 0; i < staticItems.count(); i++) {
        QDomNode itemnode = staticItems.at(i);
        if (itemnode.isElement()) {
            QDomElement presetElement = itemnode.toElement();
            QString staticCode = presetElement.attribute("code");
            int type = 0;
            bool ok;
            type = presetElement.attribute("type").toInt(&ok, 10);

            Preset preset(presetElement.attribute("name"),presetID,false);
            presetID++;
            preset.type = type;
            if (type == 0)
            {
                preset.setColor(staticCode);
            }
            if (type == 2)
            {
                QDomNodeList offsetItems = presetElement.elementsByTagName("offset");
                for (int a = 0; a < offsetItems.count(); a++) {
                    QDomNode offsetNode = offsetItems.at(a);
                    if (offsetNode.isElement()) {
                        QDomElement offsetElement = offsetNode.toElement();
                        Preset::Offset *offset = new Preset::Offset();
                        offset->colorHex = offsetElement.attribute("code");
                        offset->start = offsetElement.attribute("start").toInt();
                        offset->end = offsetElement.attribute("end").toInt();
                        offset->skip = offsetElement.attribute("skip").toInt();
                        preset.addOffset(offset, a);
                    }
                }
            }
            gColorPresetMap.insert(presetID, preset);

        }
    }

    //load dynamic presets
    for (int i = 0; i < dynamicItems.count(); i++) {
        QDomNode itemnode = dynamicItems.at(i);
        if (itemnode.isElement()) {
            QDomElement presetElement = itemnode.toElement();

            Preset preset(presetElement.attribute("name"),presetID, true, presetElement.attribute("fade").toInt(), presetElement.attribute("delay").toInt());
            QDomNodeList stepItems = presetElement.elementsByTagName("step");
            for (int a = 0; a < stepItems.count(); a++) {
                QDomNode stepNode = stepItems.at(a);
                if (stepNode.isElement()) {
                    QDomElement stepElement = stepNode.toElement();
                    int h = stepElement.attribute("h").toInt();
                    int s = stepElement.attribute("s").toInt();
                    int v = stepElement.attribute("v").toInt();

                    Preset::Step *step = new Preset::Step();
                    step->h = h;
                    step->s = s;
                    step->v = v;
                    preset.addStep(step, a);
                }
            }
            presetID++;
            gColorPresetMap.insert(presetID,preset);
        }
    }
}
int main(int argc, char *argv[])
{
    QQmlEngine *engine = new QQmlEngine(Q_NULLPTR);
    QQmlComponent component(engine, "Main.qml");
    QObject *object = component.create();

    QString returnedValue;
    QString msg = "Hello from C++";
    QMetaObject::invokeMethod(object, "myQmlFunction",
            Q_RETURN_ARG(QString, returnedValue),
            Q_ARG(QString, msg));

    qDebug() << "QML function returned:" << returnedValue;
    delete object;


    QGuiApplication a(argc, argv);
    //QQmlApplicationEngine engine;

    EventFilter filter;
    qInstallMessageHandler(systemlogHandler);
    if (gpioInitialise() < 0)
    {
        qWarning() << "Failed to open GPIO";

    } else {
        qInfo() << "GPIO Ready";
    }

    bus = smah_i2c_open("/dev/i2c-1");
    if (bus == nullptr)
    {
        qInfo() << "I2C init failed";
    } else {
        qInfo() << "I2C init successful";
        if (PCA9685_setFreq(bus, 1000) == 0)
        {
            PCA9685_init(bus);
            qInfo() << "PCA init successful";
            g_PCA9685_ready = true;
        } else {
            qInfo() << "PCA init failed";
        }
    }



    // determine our MAC addy
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (interface.name() == "wlp5s0" || interface.name() == "wlan0" || interface.name() == "eth0")
                {
                    MY_HW_ADDR = interface.hardwareAddress();
                    break;
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

    QDir::setCurrent(homeLocation + "/.smah/");
    loadZones();
    loadPresets();

    QDir::setCurrent(homeLocation + "/.smah/assets");

    QFile File("main.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    QFontDatabase::addApplicationFont("Crescent-Regular.ttf");
    QFontDatabase::addApplicationFont("Roboto-Thin.ttf");
    QFontDatabase::addApplicationFont("NotoSans-Regular.ttf");
    QFontDatabase::addApplicationFont("fa.otf");
    QFontDatabase::addApplicationFont("Vera.ttf");
    QFontDatabase::addApplicationFont("basic_sans_serif_7.ttf");


    tcpServer.startListen();
    //MainWindow mainWindow(Q_NULLPTR);
    //mainWindow.setStyleSheet(StyleSheet);

    DatagramHandler broadcaster;
    //QObject::connect(&broadcaster, SIGNAL(initiate(QHostAddress*)), &tcpServer, SLOT(initiateConnection(QHostAddress*)));

    //mainWindow.show();
    a.installEventFilter(&filter);
    //QObject::connect(&filter,SIGNAL(userActivity(QEvent*)), &mainWindow,SLOT(resetIdle(QEvent*)));
    return a.exec();
}
