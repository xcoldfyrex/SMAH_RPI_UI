#include "w_zoneoverview.h"
#include "zone.h"

extern Zone *gActiveZone;

ZoneOverviewWidget::ZoneOverviewWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    lblZoneName = new QLabel;
    topWidget->setLayout(contentLayout);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(lblZoneName,0,0);
}

void ZoneOverviewWidget::setActiveZone(Zone zone) {
    lblZoneName->setText(zone.name);
}

void ZoneOverviewWidget::switchZone(Zone zone) {
    this->lblZoneName->setText(zone.name);
}
