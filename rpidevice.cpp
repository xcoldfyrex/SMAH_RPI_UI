#include "rpidevice.h"

#include <QDebug>

RPIDevice::RPIDevice(int id, QString name, QString hwAddress)
{
    this->id = id;
    this->name = name;
    this->hwAddress = hwAddress;
}

RPIDevice::RPIDevice(QObject *parent) : QObject(parent)
{

}

RPIDevice::~RPIDevice()
{
    int a;
}

RPIDevice::PowerFunction::PowerFunction(QString name, int id, short type)
{
    this->id = id;
    this->name = name;
    this->type = type;
}

/*
void RPIDevice::updateGPIOLabels(QJsonObject payload, int zoneId)
{
    if (zoneId != this->id)
        return;
    QJsonObject power = payload["power"].toObject();
    QJsonObject lights = payload["lights"].toObject();
    QJsonObject adc = payload["adc"].toObject();
    for (int x=0; x < this->powerStatusLabels->size(); x++)
    {
        int val = power[QString::number(x)].toInt();
        QString status = "OFF";
        if (val == 0)
            status = "ON";
        this->powerStatusLabels->value(x)->setText(status);
    }
    int x = 0;
    foreach (const QJsonValue &jsonvalue, adc) {
        int value = jsonvalue.toInt();
        this->environmentMap.insert(x, value);
        x++;
    }
}

void RPIDevice::sendToNetwork(QString command, QJsonObject jsonPayload)
{
    jsonPayload["zone"] = this->getId();
    emit(requestingNetworkOut(command,jsonPayload, ""));
}
*/
