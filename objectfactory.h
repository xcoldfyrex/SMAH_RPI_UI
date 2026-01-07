#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <QObject>
#include "configuration.h"

#include "shelly.h"
#include "camera.h"
#include "zone.h"
#include "sensor.h"

class ObjectFactory : public QObject
{
    Q_OBJECT

public:
    explicit ObjectFactory(QObject *parent = nullptr);
    Q_INVOKABLE void createShellyObjects(Configuration *config);
    Q_INVOKABLE void createCameraObjects(Configuration *config);
    Q_INVOKABLE void createZoneObjects(Configuration *config);
    Q_INVOKABLE void createSensorObjects(Configuration *config);
    Q_INVOKABLE void createLightObjects(Configuration *config);
    Q_INVOKABLE void createPresetObjects(Configuration *config);
    Q_INVOKABLE void createSceneObjects(Configuration *config);


    Q_INVOKABLE QList<Shelly*> getShellyObjects() { return this->mShellyList; }
    Q_INVOKABLE QList<Camera> getCameraObjects() { return this->mCameraList; }
    Q_INVOKABLE QList<Zone*> getZoneObjects() { return this->mZoneList; }
    Q_INVOKABLE QList<Preset*> getPresetObjects() { return this->mPresetList; }
    Q_INVOKABLE QList<Scene*> getSceneObjects() { return this->mSceneList; }
    Q_INVOKABLE QList<Sensor*> getSensorObjects();

private:
    QList<Shelly*> mShellyList;
    QList<Camera> mCameraList;
    QList<Zone*> mZoneList;
    QList<Preset*> mPresetList;
    QList<Scene*> mSceneList;



    Zone *getZoneByName(QString mName);
    Shelly *getShellyByID(QString mID);


signals:
};

#endif // OBJECTFACTORY_H
