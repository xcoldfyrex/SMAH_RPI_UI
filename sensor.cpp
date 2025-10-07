#include "sensor.h"


Sensor::Sensor(QString name, int node_id, bool farenheit, QObject *parent) : QObject(parent)
{
    this->name = name;
    this->node_id = node_id;
    this->farenheit = farenheit;
}

Sensor::Sensor(QObject *parent) : QObject(parent)
{

}



