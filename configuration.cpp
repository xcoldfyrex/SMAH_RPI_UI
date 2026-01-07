#include "configuration.h"
#include "qdir.h"
#include "qforeach.h"

Configuration::Configuration()
    : QObject{}
{
    Config config;
    this->config = config;
}

QDomDocument Configuration::validateConfigFile(QString config)
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

/* loads configs that are really not intended to ever be modified by the UI */
bool Configuration::loadBaseConfiguration() {
    Config config = this->config;
    QDomDocument document = validateConfigFile("smah_config.xml");
    if (!document.isDocument())
        return false;

    QDomElement root = document.firstChildElement();

    /* ambient loop sounds. */
    QDomNodeList loopItems = root.elementsByTagName("loop");
    config.mAmbientLoopConfigurations.clear();
    foreach(QDomNode outerNode, loopItems) {
        QDomElement loopElement = outerNode.toElement();
        Configuration::AmbientLoopConfiguration loop;
        loop.mName = loopElement.attribute("name");
        loop.mFile = loopElement.attribute("file");
        config.mAmbientLoopConfigurations.append(loop);
    }

    /* each camera. */
    QDomNodeList cameraItems = root.elementsByTagName("camera");
    config.mCameraConfigurations.clear();
    foreach(QDomNode outerNode, cameraItems) {
        QDomElement cameraElement = outerNode.toElement();
        Configuration::CameraConfiguration camera;
        camera.mName = cameraElement.attribute("name");
        camera.mLowRTSP = cameraElement.attribute("low");
        camera.mMedRTSP = cameraElement.attribute("med");
        camera.mHighRTSP = cameraElement.attribute("high");
        config.mCameraConfigurations.append(camera);
    }

    /* each shelly. */
    QDomNodeList shellyItems = root.elementsByTagName("shelly");
    config.mShellyConfigurations.clear();
    foreach(QDomNode outerNode, shellyItems) {
        QDomElement shellyElement = outerNode.toElement();
        Configuration::ShellyConfiguration shelly;
        shelly.mID = shellyElement.attribute("id");
        shelly.mIP = shellyElement.attribute("ip");
        config.mShellyConfigurations.append(shelly);
    }

    /* each zone */
    QDomNodeList zoneItems = root.elementsByTagName("zone");
    config.mZoneConfigurations.clear();
    foreach(QDomNode outerNode, zoneItems) {
        QDomElement zoneElement = outerNode.toElement();
        Configuration::ZoneConfiguration zone;
        zone.mColorCode = zoneElement.attribute("cc");
        zone.mName = zoneElement.attribute("name");

        /* lights in the zone */
        QDomNodeList lightItems = zoneElement.elementsByTagName("light");
        zone.mLightConfigurations.clear();
        foreach(QDomNode lightNode, lightItems) {
            QDomElement lightElement = lightNode.toElement();
            Configuration::LightConfiguration light;
            light.mName = lightElement.attribute("name");
            light.mShellyID = lightElement.attribute("device");
            zone.mLightConfigurations.append(light);
        }

        /* sensors in the zone */
        QDomNodeList sensorItems = zoneElement.elementsByTagName("sensor");
        zone.mSensorConfigurations.clear();
        foreach(QDomNode sensorNode, sensorItems) {
            QDomElement sensorElement = sensorNode.toElement();
            Configuration::SensorConfiguration sensor;
            sensor.mName = sensorElement.attribute("name");
            sensor.mID = sensorElement.attribute("id");
            zone.mSensorConfigurations.append(sensor);
        }

        config.mZoneConfigurations.append(zone);
    }

    this->config = config;
    return false;
}


/* loads configs that are inteded to be (eventually) UI handlded */
bool Configuration::loadUserDefinedConfiguration() {
    Config config = this->config;
    QDomDocument document = validateConfigFile("smah_userdefined.xml");
    if (!document.isDocument())
        return false;

    QDomElement root = document.firstChildElement();

    /* each RGBW preset. */
    QDomNodeList presetItems = root.elementsByTagName("static");
    config.mPresetConfigurations.clear();
    foreach(QDomNode outerNode, presetItems) {
        QDomElement presetlement = outerNode.toElement();
        Configuration::PresetConfiguration preset;
        preset.mName = presetlement.attribute("name");
        preset.mColorCode = presetlement.attribute("code");
        config.mPresetConfigurations.append(preset);
    }

    /* each scene */
    QDomNodeList sceneGroupItems = root.elementsByTagName("scene");
    config.mSceneGroupConfigurations.clear();
    foreach(QDomNode outerNode, sceneGroupItems) {
        QDomElement sceneGroupElement = outerNode.toElement();
        Configuration::SceneGroupConfiguration scenegroup;
        scenegroup.mName = sceneGroupElement.attribute("name");
        scenegroup.mZones.append(sceneGroupElement.attribute("zone"));
        // missing zones
        QDomNodeList sceneItems = sceneGroupElement.elementsByTagName("item");
        /* each item in the scene */
        foreach(QDomNode itemNode, sceneItems) {
            QDomElement sceneItemElement = itemNode.toElement();
            Configuration::SceneItemConfiguration scene;
            scene.mColorCode = sceneItemElement.attribute("value");
            scene.mDevice = sceneItemElement.attribute("device");
            scene.mState = sceneItemElement.attribute("state").toInt();
            scenegroup.mSceneItems.append(scene);
        }
        config.mSceneGroupConfigurations.append(scenegroup);
    }

    this->config = config;

    return false;
}
