#include "zone.h"

Zone::Zone(int id, QString name)
{
    this->id = id;
    this->name = name;
    //qRegisterMetaType<Zone>("Zone");
}

Zone::Zone()
{
    //qRegisterMetaType<Zone>("Zone");
}

void Zone::addDevice(RPIDevice *device)
{
    if (this->deviceList.contains(device->getHwAddress()))
        return;
    this->deviceList.insert(device->getHwAddress(),device);
}

Light* Zone::getLightById(int id)
{
    QList<Light*> tempIterator;
    foreach (QVariant v, this->getLightList())
    {
        tempIterator << v.value<Light*>();
    }
    for (Light *light : tempIterator)
    {
        if (light->getId() == id)
            return light;
    }
    return Q_NULLPTR;
}

Sensor* Zone::getSensorById(int id)
{
    for (Sensor *sensor : this->getSensorList())
    {
        if (sensor->getNodeId() == id)
            return sensor;
    }
    return nullptr;
}
