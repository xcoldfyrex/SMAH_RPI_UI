#include "w_zoneenvironment.h"
#include "math.h"
#define ZeroPercentVoltage 0.958

ZoneEnvironmentPanel::ZoneEnvironmentPanel(QWidget *parent, Zone *zone) : QWidget(parent)
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

    lblZoneEnvHeader = new QLabel(zone->getName());
    lblZoneEnvData = new QLabel();

    lblZoneEnvHeader->setObjectName("lblZoneEnvHeader");
    lblZoneEnvData->setObjectName("lblZoneEnvData");
    contentLayout->addWidget(lblZoneEnvIcon,0,0,2,2);
    contentLayout->setAlignment(Qt::AlignLeft);

    contentLayout->addWidget(this->lblZoneEnvHeader,0,2, Qt::AlignLeft);
    contentLayout->addWidget(this->lblZoneEnvData,1,2, Qt::AlignLeft);
    topWidget->setLayout(contentLayout);

    updateTimer = new QTimer();
    updateTimer->setInterval(1000);
    updateTimer->start();

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(enviroUpdate()),Qt::DirectConnection);
}

void ZoneEnvironmentPanel::enviroUpdate()
{
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
