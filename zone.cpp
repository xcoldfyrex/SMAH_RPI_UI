#include "zone.h"

Zone::Zone(int id, QString name, QString cc)
{
    this->id = id;
    this->name = name;
    this->cc = cc;
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

void Zone::addScene(Scene *scene)
{
    /*
    if (this->sceneList.contains(scene.getName()))
    {
        qWarning() << "Scene" << scene.getName() << "already exists in zone" << this->getName();
        return;
    }
*/
    this->sceneList.append(QVariant::fromValue(scene));
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
