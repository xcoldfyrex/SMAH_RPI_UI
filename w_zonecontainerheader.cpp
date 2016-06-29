#include "w_zonecontainerheader.h"

extern Zone *gActiveZone;

ZoneContainerHeaderWidget::ZoneContainerHeaderWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);

    lblZoneName = new QLabel("Zone: N/A");
    lblZoneLightPreset = new QLabel("Preset: N/A");
    topWidgetLayout->addWidget(lblZoneName);
    topWidgetLayout->addWidget(lblZoneLightPreset);

    lblZoneName->setObjectName("lblZoneOverviewHeader");
    lblZoneLightPreset->setObjectName("lblZoneOverviewHeader");

}

void ZoneContainerHeaderWidget::setActiveZone(Zone zone) {
    lblZoneName->setText(zone.name);
}

void ZoneContainerHeaderWidget::switchZone(Zone zone) {
    this->lblZoneName->setText("Zone: " + zone.name);
    *gActiveZone = zone;
}

void ZoneContainerHeaderWidget::changePreset(QString preset) {
    this->lblZoneLightPreset->setText("Preset: " + preset);
}
