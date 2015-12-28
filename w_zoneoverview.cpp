#include "w_zoneoverview.h"
#include "zone.h"

extern Zone *gActiveZone;

ZoneOverviewWidget::ZoneOverviewWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    lblZoneName = new QLabel("ZONE");
    lblZoneLightPreset = new QLabel("PRESET");
    lblZoneTemp = new QLabel("TEMP");
    lblZoneRH = new QLabel("RH");

    lblZoneName->setObjectName("lblZoneName");

    topWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(lblZoneName,0,0);
    contentLayout->addWidget(lblZoneLightPreset,1,0);
    contentLayout->addWidget(lblZoneTemp,2,0);
    contentLayout->addWidget(lblZoneRH,3,0);
}

void ZoneOverviewWidget::setActiveZone(Zone zone) {
    lblZoneName->setText(zone.name);
}

void ZoneOverviewWidget::switchZone(Zone zone) {
    this->lblZoneName->setText("Selected zone: " + zone.name);
}

void ZoneOverviewWidget::changePreset(QString preset) {
    this->lblZoneLightPreset->setText("Active preset: " + preset);
}

void ZoneOverviewWidget::changeRH(QString rh) {
    this->lblZoneRH->setText("Current RH: " + rh);
}

void ZoneOverviewWidget::changeTemperature(QString temp) {
    this->lblZoneTemp->setText("Current temperature: " + temp);
}
