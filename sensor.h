#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>


class Sensor
{
public:
    Sensor(QString name, int node_id, int device_id);
    float getTemperature() { return this->temperature; }
    float getHumidity() { return this->humidity; }
    short getLux() { return this->lux; }
    int getNodeId() { return this->node_id; }
    int getDeviceId() { return this->device_id; }
    QString getName() { return this->name; }
    void setTemperature(float temperature) { this->temperature = temperature; }
    void setHumidity(float humidity) { this->humidity = humidity; }
    void setLux(short lux) { this->lux = lux; }
    void setTemperatureFromRaw(float temperature);
    void setHumidityFromRaw(float humidity);

private:
    float temperature = 0;
    float humidity = 0;
    float raw_temperature = 0;
    float raw_humidity = 0;
    short lux = 0;
    short motion_level = 0;
    int node_id;
    int device_id;
    QString name;
};

#endif // SENSOR_H
