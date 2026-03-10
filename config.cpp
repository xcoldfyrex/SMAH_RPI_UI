#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QMap>
#include <QString>

#include "config.h"
#include "camera.h"
#include "qapplication.h"
#include "zone.h"
#include "preset.h"
#include "shelly.h"
#include "light.h"
#include "scheduled_actions.h"
#include "scene.h"

QList <Sensor*> g_sensorList;
QMap<QString, Zone*> g_zoneMap;
QMap<int, Preset*> g_colorPresetMap;
QMap <QString, RPIDevice*> g_deviceList;
QMap <QString, Shelly*> g_shellyList;
QMap <int, Light*> g_lightMap;
QList<ScheduledActions*> g_actionList;
QList <Camera> g_cameraList;


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
    /*
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
*/
}

void loadPresets()
{
    QDomDocument document = validateConfigFile("light_presets.xml");
    if (!document.isDocument())
        return;
    QDomElement root = document.firstChildElement();

    QDomNodeList staticItems = root.elementsByTagName("static");
    QDomNodeList dynamicItems = root.elementsByTagName("dynamic");

    //load static presets
    /*
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
