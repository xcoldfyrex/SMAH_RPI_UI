#include "w_zoneenvironment.h"
#include "math.h"
#define ZeroPercentVoltage 0.958

ZoneEnvironmentPanel::ZoneEnvironmentPanel(QWidget *parent, Zone zone) : QWidget(parent)
{

    this->topWidget = new QWidget;
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    this->zone = zone;

    QImage *imgZoneEnvIcon = new QImage("thermometer.png");
    QLabel *lblZoneEnvIcon = new QLabel(" ");
    *imgZoneEnvIcon = imgZoneEnvIcon->scaled(32,32,Qt::KeepAspectRatio);
    lblZoneEnvIcon->setPixmap(QPixmap::fromImage(*imgZoneEnvIcon));
    lblZoneEnvIcon->resize(32,32);

    lblZoneEnvData = new QEngravedLabel();

    lblZoneEnvData->setObjectName("lblZoneEnvData");
    contentLayout->addWidget(lblZoneEnvIcon,0,0,2,2);
    contentLayout->setAlignment(Qt::AlignLeft);

    contentLayout->addWidget(this->lblZoneEnvData,0,2, Qt::AlignLeft);
    topWidget->setLayout(contentLayout);
    topWidget->resize(topWidget->height(),300);

    updateTimer = new QTimer();
    updateTimer->setInterval(1000);
    updateTimer->start();
    delete imgZoneEnvIcon;
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(enviroUpdate()),Qt::DirectConnection);
}

void ZoneEnvironmentPanel::enviroUpdate()
{
    if (this->zone.getSensorList().size() == 0)
        return;
    for (Sensor *sensor : this->zone.getSensorList())
    {
        QString text;
        text += sensor->getName() + "\n";
        text += QString::number(sensor->getTemperature()) + " F\n";
        if (sensor->getHumidity() > 0)
            text += QString::number(sensor->getHumidity()) + "% RH\n\r";

        lblZoneEnvData->setText(text);
    }

    //float temp = ceilf(rawVoltage(zone->environmentMap.value(0) * 100) * 100) / 100;
    //float rh_voltage = rawVoltage(zone->environmentMap.value(1));
    //float RH = ceilf((((rh_voltage - .958) / .0307) * 100)) / 100;
    //if (RH < 0)
    //    RH = 0;
    //lblZoneEnvData->setText(QString::number(temp) + " F\n" + QString::number(RH) + " %");
}

float ZoneEnvironmentPanel::rawVoltage(int reading)
{
    float ref = 4.95;
    return (reading * ref) / float(4096);
}
