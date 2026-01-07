#include "objectfactory.h"

ObjectFactory::ObjectFactory(QObject *parent)
    : QObject{parent}
{}

void ObjectFactory::createShellyObjects(Configuration *config) {
    foreach (Configuration::ShellyConfiguration item, config->getConfiguration().mShellyConfigurations) {
        Shelly *shelly = new Shelly(item.mIP, item.mID);
        this->mShellyList.append(shelly);
    }
}

void ObjectFactory::createCameraObjects(Configuration *config) {
    foreach (Configuration::CameraConfiguration item, config->getConfiguration().mCameraConfigurations) {
        Camera camera(item.mName, item.mLowRTSP, item.mMedRTSP, item.mHighRTSP);
        this->mCameraList.append(camera);
    }
}

void ObjectFactory::createZoneObjects(Configuration *config) {
    foreach (Configuration::ZoneConfiguration item, config->getConfiguration().mZoneConfigurations) {
        Zone *zone = new Zone(item.mName, item.mColorCode);
        this->mZoneList.append(zone);
    }
}

void ObjectFactory::createSensorObjects(Configuration *config) {
    foreach (Configuration::ZoneConfiguration zone, config->getConfiguration().mZoneConfigurations) {
        foreach (Configuration::SensorConfiguration item, zone.mSensorConfigurations) {
            Sensor *sensor = new Sensor(item.mName, item.mID.toInt());
            getZoneByName(zone.mName)->addSensor(sensor);
        }
    }
}

void ObjectFactory::createLightObjects(Configuration *config) {
    foreach (Configuration::ZoneConfiguration zone, config->getConfiguration().mZoneConfigurations) {
        foreach (Configuration::LightConfiguration item, zone.mLightConfigurations) {
            Light *light = new Light(item.mName, getShellyByID(item.mShellyID));
            getZoneByName(zone.mName)->addLight(light);
        }
    }
}

void ObjectFactory::createPresetObjects(Configuration *config) {
    foreach (Configuration::PresetConfiguration item, config->getConfiguration().mPresetConfigurations) {
        Preset *preset = new Preset(item.mName, item.mColorCode);
        this->mPresetList.append(preset);
    }
}

void ObjectFactory::createSceneObjects(Configuration *config) {
    foreach (Configuration::SceneGroupConfiguration item, config->getConfiguration().mSceneGroupConfigurations) {
        Scene *scene = new Scene(item.mName);
        foreach (Configuration::SceneItemConfiguration sceneItem, item.mSceneItems)
        {
            scene->addItem(getShellyByID(sceneItem.mDevice), sceneItem.mColorCode, sceneItem.mState);
        }
        this->mSceneList.append(scene);
        /* TODO: make this the list */
        getZoneByName(item.mZones[0])->addScene(scene);
    }
}

Zone *ObjectFactory::getZoneByName(QString mName) {
    foreach (Zone *zone, this->mZoneList) {
        if (zone->getName() == mName)
            return zone;
    }
    return NULL;
}

Shelly *ObjectFactory::getShellyByID(QString mID) {
    foreach (Shelly *shelly, this->mShellyList) {
        if (shelly->getID() == mID)
            return shelly;
    }
    return NULL;
}

QList<Sensor*> ObjectFactory::getSensorObjects() {
    QList<Sensor*> tempList;
    foreach (Zone *zone, this->mZoneList) {
        foreach (Sensor *sensor, zone->getSensorList()) {
            tempList.append(sensor);
        }
    }
    return tempList;
}
