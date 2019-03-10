#include "sensor.h"
#include "commandrouter.h"

extern int MY_DEVICE_ID;

Sensor::Sensor(QString name, int node_id, int device_id, bool farenheit)
{
    this->name = name;
    this->node_id = node_id;
    this->device_id = device_id;
    this->farenheit = farenheit;
}

void Sensor::setTemperature(float temperature)
{
    this->temperature = temperature;
    if (this->getDeviceId() == MY_DEVICE_ID)
        broadcastMessage(this->getNodeId(), 1, temperature, 0);
}

void Sensor::setHumidity(float humidity)
{
    this->humidity = humidity;
    if (this->getDeviceId() == MY_DEVICE_ID)
        broadcastMessage(this->getNodeId(), 1, humidity, 1);
}

void Sensor::setLux(short lux)
{
    this->lux = lux;
    if (this->getDeviceId() == MY_DEVICE_ID)
        broadcastMessage(this->getNodeId(),1, lux, 2);
}
