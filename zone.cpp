#include "zone.h"

Zone::Zone(int id, QString name)
{
    this->id = id;
    this->name = name;
    qRegisterMetaType<Zone>("Zone");
    //QList<QWidget*> *pageStack = new QList<QWidget*>();
}

Zone::Zone()
{
    qRegisterMetaType<Zone>("Zone");
}

void Zone::addDevice(RPIDevice device)
{
    if (this->deviceList.contains(device.getHwAddress()))
        return;
    this->deviceList.insert(device.getHwAddress(),device);
}

Light* Zone::getLightById(int id)
{
    for (Light *light : this->getLightList())
    {
        if (light->getId() == id)
            return light;
    }
    return NULL;
}
