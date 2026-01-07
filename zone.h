#ifndef LIBSMAHZONE_H
#define LIBSMAHZONE_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDataStream>
#include <QObject>
#include <QVariantList>

#include "rpidevice.h"
#include "light.h"
#include "sensor.h"
#include "scene.h"

typedef QMap<QString, Sensor*> SensorListMap;

Q_DECLARE_METATYPE(SensorListMap)


class Zone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString getName READ getName CONSTANT);
    Q_PROPERTY(QString getCC READ getCC CONSTANT);
    Q_PROPERTY(QVariantList getLightList READ getLightList CONSTANT);
    Q_PROPERTY(SensorListMap getSensorList READ getSensorList CONSTANT);
    Q_PROPERTY(QVariantList getSceneList READ getSceneList CONSTANT);


public:
    Q_INVOKABLE
        Q_INVOKABLE void addScene(Scene *scene);

    Zone(QString name, QString cc);
    virtual ~Zone() {}

    void setName(QString name)
    {
        this->name = name;
    }
    void addLight(Light *light)
    {
        this->zoneLightList.append(QVariant::fromValue(light));
    }

    void addSensor(Sensor *sensor)
    {
        this->sensorList.insert(sensor->getName(), sensor);
    }

    QString getName() const { return this->name; }
    QString getCC() const { return this->cc.toUpper(); }

    /* these are all const.
     * refeacotr if we want to dynamic load */

    QMap<QString, RPIDevice*> getDeviceList() const { return this->deviceList; }
    QMap<QString, Sensor*> getSensorList() const { return this->sensorList; }

    QVariantList getSceneList() const { return this->sceneList; }
    QVariantList getLightList() const { return this->zoneLightList; }
    //Light *getLightById(int id);
    Sensor *getSensorById(int id);
    void addDevice(RPIDevice *device);

private:
    QString name;
    QString cc = "FF";
    QMap <QString, RPIDevice*> deviceList;
    QMap <QString, Sensor*> sensorList;
    QVariantList sceneList;
    QVariantList zoneLightList;
};


#endif // LIBSMAHZONE_H
