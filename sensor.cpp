#include "sensor.h"

Sensor::Sensor(QString name, int node_id, int device_id)
{
    this->name = name;
    this->node_id = node_id;
    this->device_id = device_id;
}
