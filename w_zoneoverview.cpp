#include "w_zoneoverview.h"

ZoneOverviewWidget::ZoneOverviewWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    lblZoneTemp = new QLabel("TEMP");
    lblZoneRH = new QLabel("RH");

    topWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(lblZoneTemp,2,0);
    contentLayout->addWidget(lblZoneRH,3,0);

}

void ZoneOverviewWidget::changeRH(QString rh) {
    this->lblZoneRH->setText("Current RH: " + rh);
}

void ZoneOverviewWidget::changeTemperature(QString temp) {
    this->lblZoneTemp->setText("Current temperature: " + temp);
}
