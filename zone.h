#ifndef LIBSMAHZONE_H
#define LIBSMAHZONE_H

#include <QString>
#include <QMap>
#include <QList>
#include <QDataStream>
#include <QObject>
#include <QWidget>

#include "rpidevice.h"
#include "light.h"
#include "sensor.h"

class Zone {

public:
    Zone(int id, QString name);
    Zone();
    virtual ~Zone() {}
    int getId() const { return this->id; }
    void setId(int id) { this->id = id; }
    void setName(QString name)
    {
        this->name = name;
    }
    void addLight(Light *light)
    {
            this->zoneLightList.insert(light->getName(), light);
    }

    void addSensor(Sensor *sensor)
    {
            this->sensorList.insert(sensor->getName(), sensor);
    }

    QString getName() const { return this->name; }
    QMap<QString, RPIDevice> getDeviceList() const { return this->deviceList; }
    QMap<QString, Sensor*> getSensorList() const { return this->sensorList; }
    QMap <QString, Light*> getLightList() const { return this->zoneLightList; }
    Light *getLightById(int id);
    Sensor *getSensorById(int id);
    QList<QWidget*> pageStack;
    void addDevice(RPIDevice device);

private:
    int id;
    QString name;
    QMap <QString, RPIDevice> deviceList;
    QMap <QString, Sensor*> sensorList;
    QMap <QString, Light*> zoneLightList;
};


#endif // LIBSMAHZONE_H
