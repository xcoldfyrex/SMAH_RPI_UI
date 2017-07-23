#include "w_zonecontainerheader.h"

ZoneContainerHeaderWidget::ZoneContainerHeaderWidget(Zone *zone, QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);

    lblZoneName = new QLabel("Selected zone: " + zone->name);
    lblZoneLightPreset = new QLabel("Preset: N/A");
    topWidgetLayout->addWidget(lblZoneName);
    topWidgetLayout->addWidget(lblZoneLightPreset);

    lblZoneName->setObjectName("lblZoneOverviewHeader");
    lblZoneLightPreset->setObjectName("lblZoneOverviewHeader");

}

void ZoneContainerHeaderWidget::changePreset(QString preset) {
    this->lblZoneLightPreset->setText("Preset: " + preset);
}
