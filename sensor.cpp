#include "sensor.h"

Sensor::Sensor(QString name, int node_id, QObject *parent) : QObject(parent)
{
    this->name = name;
    this->node_id = node_id;
}
