#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QMap>
#include <QDateTime>
#include <QDate>

#include "tcpconnectionfactory.h"
#include "zwavemanager.h"


extern int MY_DEVICE_ID;
extern TCPConnectionFactory tcpServer;
extern uint32  g_homeId;


class Sensor : public QObject
{
    Q_OBJECT
public:
    Sensor(QString name, int node_id, int device_id, bool farenheit=false, uint32 home_id = 0);
    explicit Sensor(QObject *parent = nullptr);
    bool isFarenheit() { return this->farenheit; }
    float getTemperature() {
        if (this->isFarenheit())
            return this->getValue(1);
        return this->getValue(1) * 9/5 + 32;
    }
    float getLux() { return this->getValue(3); }
    float getHumidity() { return this->getValue(5); }
    float getUV() { return this->getValue(27); }
    int getNodeId() { return this->node_id; }
    int getDeviceId() { return this->device_id; }
    int getBattery() { return this->battery; }
    qint64 getLastUpdate() { return this->updated; }
    void setLastUpdate(qint64 ts) { this->updated = ts; }

    QString getName() { return this->name; }
    uint32 getHome_id() { return this->home_id; }

    //void setTemperatureFromRaw(float temperature);
    //void setHumidityFromRaw(float humidity);
    QMap<int, float> getValues() { return  this->values; }
    void setValue(int index, float value) {
        this->values[index] = value;
        if (this->getHome_id() == g_homeId)
            tcpServer.broadcastMessage(this->getNodeId(), 1, value, index);
        setLastUpdate(QDateTime::currentSecsSinceEpoch());
    }
    float getValue(int index) {
        if (this->values.contains(index))
            return this->values[index];
        return 0;
    }
    void setBattery(int level) { this->battery = level; }

private:
    bool farenheit = false;
    float temperature = 0; /* DEPRECATE THIS */
    float humidity = 0; /* DEPRECATE THIS */
    //float raw_temperature = 0; /* DEPRECATE THIS */
    //float raw_humidity = 0;
    short lux = 0; /* DEPRECATE THIS */
    //short motion_level = 0;
    int battery = 0;
    int node_id;
    int device_id;
    qint64 updated = 0;
    QString name;
    uint32 home_id;
    QMap<int, float> values;
};

#endif // SENSOR_H
