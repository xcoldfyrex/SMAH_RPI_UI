#include <QApplication>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>
#include <QNetworkInterface>

#include "zone.h"
#include "light.h"
#include "mainwindow.h"
#include "preset.h"
#include "logger.h"
#include "datagramhandler.h"
#include "pigpio.h"
#include "gpio_defs.h"
#include "tcpserver.h"
#include "pca9685.h"
#include "i2c/i2c.h"

QMap<QString, Zone> gZoneMap;
QMap<int, Preset> gColorPresetMap;
QList<ClientSocket*> g_clientMap;
QMap <QString, RPIDevice> g_deviceList;
QMap <int, Light*> g_lightMap;
QMap <int, int> g_nodeValues;
QString MY_HW_ADDR;
QString MY_IP_ADDR;
int MY_DEVICE_ID;
smah_i2c bus;
QString homeLocation;

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
                    RPIDevice rpidevice(
                                powerElement.attribute("id").toInt(),
                                powerElement.attribute("name"),
                                powerElement.attribute("hw")
                                );
                    zone.addDevice(rpidevice);
                    g_deviceList.insert(powerElement.attribute("hw"),rpidevice);
                    if (rpidevice.getHwAddress() == MY_HW_ADDR)
                        MY_DEVICE_ID = rpidevice.getId();
                    //zone->powerControls.insert(powerElement.attribute("id").toInt(), powerElement.attribute("name"));
                }
            }
            /* each light in the zone */
            QDomNodeList lightItems = element.elementsByTagName("light");
            for (int a = 0; a < lightItems.count(); a++) {
                QDomNode lightNode = lightItems.at(a);
                if (lightNode.isElement()) {
                    QDomElement lightElement = lightNode.toElement();
                    Light *light = new Light(lightElement.attribute("id").toInt(),
                                             lightElement.attribute("name"),
                                             lightElement.attribute("type").toInt(),
                                             lightElement.attribute("device").toInt(),
                                             lightElement.attribute("bank").toInt()
                                             );
                    zone.addLight(light);
                    g_lightMap.insert(lightElement.attribute("id").toInt(), light);
                }
            }
            //QDomNodeList powerItems = element.elementsByTagName("power");
            //for (int a = 0; a < powerItems.count(); a++) {
            // /   QDomNode powerNode = powerItems.at(a);
            //    if (powerNode.isElement()) {
            //        QDomElement powerElement = powerNode.toElement();
            //zone->powerControls.insert(powerElement.attribute("id").toInt(), powerElement.attribute("name"));
            //    }
            //}
            //gZoneMapDELETEME->insert(zone->id, zone);
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

    int presetID = 0;
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
    QApplication a(argc, argv);
    qInstallMessageHandler(systemlogHandler);

    if (gpioInitialise() < 0)
    {
        qWarning() << "Failed to open GPIO";

    } else {
        gpioPWM(GPIO_PIN_RED, 0);
        gpioPWM(GPIO_PIN_GREEN, 0);
        gpioPWM(GPIO_PIN_BLUE, 0);
        gpioPWM(GPIO_PIN_WHITE, 0);
        qInfo() << "GPIO ports reset";

    }

    bus = smah_i2c_open("/dev/i2c-1");
    if (bus == 0)
    {
        qWarning() << "Failed to open i2c bus";
    } else {
        PCA9685_setFreq(bus, 1000);
        PCA9685_init(bus);
        PCA9685_setDutyCycle(bus,0, 0);
        PCA9685_setDutyCycle(bus,1, 0);
        PCA9685_setDutyCycle(bus,2, 0);
        PCA9685_setDutyCycle(bus,3, 0);
        qInfo() << "i2c bus opened";
    }



    // determine our MAC addy
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (interface.name() == "wlp36s0" || interface.name() == "wlan0")
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
    QFontDatabase::addApplicationFont("DigitaldreamFat.ttf");

    TCPServer tcpServer;
    DatagramHandler broadcaster;

    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();

}
