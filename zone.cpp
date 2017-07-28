#include "network.h"
#include "zone.h"

#include <QDebug>

extern NetworkThread *networkThread;

Zone::Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasPower, bool hasEnviro, QObject *parent)
    : QObject(parent)
{
    this->id = id;
    this->name = name;
    this->hasLedRGB = hasLedRGB;
    this->hasLedWhite = hasLedWhite;
    this->hasEnviro = hasEnviro;
    this->hasPower = hasPower;
    zoneSelector = new QPushButton(this->name);
    zoneFunctionContainer = new ZoneContainerWidget(this);
    powerStatusLabels = new QMap<int, QLabel*>();
    connect(networkThread,SIGNAL(zoneGPIOArrived(QJsonObject,int)), this, SLOT(updateGPIOLabels(QJsonObject,int)));
}

Zone::Zone()
{
    this->hasEnviro = false;
}

int Zone::getActivePreset()
{
    return this->activePreset;
}

void Zone::setActivePreset(int preset)
{
    this->activePreset = preset;
}

Zone::PowerFunction::PowerFunction(int id, QString name)
{
    this->id = id;
    this->name = name;
}

Zone::PowerFunction::PowerFunction()
{

}

void Zone::updateGPIOLabels(QJsonObject payload, int zoneId)
{
    if (zoneId != this->id)
        return;
    QJsonObject power = payload["power"].toObject();
    QJsonObject lights = payload["lights"].toObject();
    QJsonObject adc = payload["adc"].toObject();
    for (int x=0; x < this->powerStatusLabels->size(); x++)
    {
        int val = power[QString::number(x)].toInt();
        QString status = "ON";
        if (val == 0)
            status = "OFF";
        this->powerStatusLabels->value(x)->setText(status);
    }
    int x = 0;
    foreach (const QJsonValue &jsonvalue, adc) {
        int value = jsonvalue.toInt();
        this->environmentMap.insert(x, value);
        x++;
    }


/*
    qDebug() << lights["R"].toInt();
    qDebug() << lights["G"].toInt();
    qDebug() << lights["B"].toInt();
    qDebug() << lights["W"].toInt();
    */

}
