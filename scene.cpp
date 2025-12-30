#include "scene.h"

Scene::Scene()
{

}

Scene::Scene(QString name)
{
    this->name = name;
}

void Scene::activate()
{
    for (mFunctions item: mItemList)
    {
        if (item.device->getApp() == "PlusRGBWPM") {
            item.device->setRGBW(item.val.toString());
            item.device->setState(item.state);

        }
        if (item.device->getApp() == "Plus1PM") {
            item.device->setState(item.state);
        }
        if (item.device->getApp() == "PlusWallDimmer") {
            item.device->setBrightness(item.val.toInt());
            item.device->setState(item.state);
        }
    }
}

void Scene::addItem(Shelly *shelly, QVariant val, bool state)
{
    mFunctions tempValues;

    tempValues.device = shelly;
    tempValues.val = val;
    tempValues.state = state;

    mItemList.append(tempValues);
}
