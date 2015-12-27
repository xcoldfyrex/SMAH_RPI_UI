#include "w_zoneoverview.h"

extern QString activeZone;

ZoneOverviewWidget::ZoneOverviewWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    lblZoneName = new QLabel;
    topWidget->setLayout(contentLayout);
    lblZoneName->setText(activeZone);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(lblZoneName,0,0);
}

