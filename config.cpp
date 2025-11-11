#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QString>

#include "config.h"
#include "shellyrelay.h"
#include "shellyrgbw.h"
#include "zone.h"
#include "preset.h"
#include "shelly.h"
#include "light.h"
#include "scheduled_actions.h"

QList <Sensor*> g_sensorList;
QMap<QString, Zone*> g_zoneMap;
QMap<int, Preset*> g_colorPresetMap;
QMap <QString, RPIDevice*> g_deviceList;
QMap <QString, ShellyRGBW*> g_shellyRGBWList;
QMap <int, Light*> g_lightMap;
QList<ScheduledActions*> g_actionList;

extern QString MY_HW_ADDR;

QDomDocument validateConfigFile(QString config)
{
    QDomDocument document;
    QFile zoneXMLFile(config);
    if (!zoneXMLFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not load" << config;
        return document;
    }
    if (!document.setContent(&zoneXMLFile)) {
        zoneXMLFile.close();
        qWarning() << "Could not parse" << config;
    }
    zoneXMLFile.close();
    return document;
}

void loadActions()
{
    QDomDocument document = validateConfigFile("smah_actions.xml");
    if (!document.isDocument())
        return;
    QDomElement root = document.firstChildElement();

    QDomNodeList groupItems = root.elementsByTagName("grouping");
    for (int a = 0; a < groupItems.count(); a++) {
        QDomNode groupNode = groupItems.at(a);
        if (groupNode.isElement()) {
            QDomElement groupElement = groupNode.toElement();
            ScheduledActions *action = new ScheduledActions();
            action->add_action(groupElement);
            g_actionList.append(action);
        }
    }
}

void loadZones()
{
    QDomDocument document = validateConfigFile("smah_zones.xml");
    if (!document.isDocument())
        return;
    QDomElement root = document.firstChildElement();

    /* each shelly. must be done before lights */
    QDomNodeList shellyItems = root.elementsByTagName("shelly");
    for (int a = 0; a < shellyItems.count(); a++) {
        QDomNode shellyNode = shellyItems.at(a);
        if (shellyNode.isElement()) {
            QDomElement shellyElement = shellyNode.toElement();
            QString type = shellyElement.attribute("type");
            if (type == "rgbw") {
                ShellyRGBW *shelly = new ShellyRGBW(
                    shellyElement.attribute("ip"),
                    shellyElement.attribute("id")
                    );
                g_shellyRGBWList.insert(shellyElement.attribute("id"), shelly);
            }
            if (type == "relay") {
                ShellyRelay *shelly = new ShellyRelay(
                    shellyElement.attribute("ip"),
                    shellyElement.attribute("id")
                    );
                g_shellyRGBWList.insert(shellyElement.attribute("id"), shelly);
            }

        }
    }
    QDomNodeList zoneItems = root.elementsByTagName("zone");
    /* enumrate zones */
    for (int i = 0; i < zoneItems.count(); i++) {
        QDomNode itemnode = zoneItems.at(i);
        if (itemnode.isElement()) {
            QDomElement element = itemnode.toElement();

            Zone *zone = new Zone(
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
                    zone->addDevice(rpidevice);
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
                    if (g_shellyRGBWList.contains(lightElement.attribute("device"))) {
                        Light *light = new Light(lightElement.attribute("id").toInt(),
                                                 lightElement.attribute("name"),
                                                 lightElement.attribute("type").toInt(),
                                                 g_shellyRGBWList.value(lightElement.attribute("device"))
                                                 );
                        zone->addLight(light);
                        g_lightMap.insert(lightElement.attribute("id").toInt(), light);
                    } else {
                        qWarning() << "Failed to get shelly object from" << lightElement.attribute("device");
                    }
                }
            }

            /* each sensor device in the zone */
            QDomNodeList sensors = element.elementsByTagName("sensor");
            for (int a = 0; a < sensors.count(); a++) {
                QDomNode sensorNode = sensors.at(a);
                if (sensorNode.isElement()) {
                    QDomElement sensorElement = sensorNode.toElement();
                    Sensor *sensor = new Sensor(
                        sensorElement.attribute("name"),
                        sensorElement.attribute("id").toShort(),
                        sensorElement.attribute("farenheit").toShort()
                        );
                    zone->addSensor(sensor);
                    g_sensorList.append(sensor);
                }
            }
            g_zoneMap.insert(zone->getName(),zone);
        }
    }
}

void loadPresets()
{
    QDomDocument document = validateConfigFile("light_presets.xml");
    if (!document.isDocument())
        return;
    QDomElement root = document.firstChildElement();

    short presetID = 0;
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

            Preset *preset = new Preset(presetElement.attribute("name"),presetID,false);
            presetID++;
            preset->type = type;
            if (type == 0)
            {
                preset->setColor(staticCode);
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
                        preset->addOffset(offset, a);
                    }
                }
            }
            g_colorPresetMap.insert(presetID, preset);

        }
    }

    //load dynamic presets
    //return; //for now
    ///*
    for (int i = 0; i < dynamicItems.count(); i++) {
        QDomNode itemnode = dynamicItems.at(i);
        if (itemnode.isElement()) {
            QDomElement presetElement = itemnode.toElement();
            Preset *preset = new Preset(presetElement.attribute("name"),presetID, true, presetElement.attribute("fade").toInt(), presetElement.attribute("delay").toInt());
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
                    preset->addStep(step, a);
                }
            }
            presetID++;
            g_colorPresetMap.insert(presetID,preset);
        }
    }
    //*/
}
