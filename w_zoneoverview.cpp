#include "math.h"
#include "w_zoneoverview.h"

extern Zone *gActiveZone;

ZoneOverviewWidget::ZoneOverviewWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    lblZoneTemp = new QLabel("Tempurate: 0");
    lblZoneRH = new QLabel("Humidty: 0%");

    topWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(lblZoneTemp,2,0);
    contentLayout->addWidget(lblZoneRH,3,0);

    QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    contentLayout->addItem(verticalSpacer,4,0);

    updateTimer = new QTimer();
    updateTimer->setInterval(1000);
    updateTimer->start();

    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateReadings()),Qt::DirectConnection);

}

void ZoneOverviewWidget::updateReadings()
{
    Zone *zone = gActiveZone;
    QList<int> envData = zone->environmentMap.value(zone->id);
    float temp = ceilf(rawVoltage(envData.value(0) * 100) * 100) / 100;
    float rh_voltage = rawVoltage(envData.value(1));
    float RH = ceilf((((rh_voltage - .958) / .0307) * 100)) / 100;
    if (RH < 0)
        RH = 0;
    this->lblZoneRH->setText("Current RH: " +QString::number(RH));
    this->lblZoneTemp->setText("Current temperature: " + QString::number(temp));

}

float ZoneOverviewWidget::rawVoltage(int reading)
{
    float ref = 4.95;
    return (reading * ref) / float(4096);
}
