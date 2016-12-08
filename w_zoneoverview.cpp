#include "w_zoneoverview.h"

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

}

void ZoneOverviewWidget::changeRH(QString rh) {
    this->lblZoneRH->setText("Current RH: " + rh);
}

void ZoneOverviewWidget::changeTemperature(QString temp) {
    this->lblZoneTemp->setText("Current temperature: " + temp);
}
