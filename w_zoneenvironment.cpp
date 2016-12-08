#include "w_zoneenvironment.h"

ZoneEnvironmentPanel::ZoneEnvironmentPanel(QWidget *parent, Zone *zone) : QWidget(parent)
{

    this->topWidget = new QWidget;
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    QImage *imgZoneEnvIcon = new QImage("thermometer.png");
    QLabel *lblZoneEnvIcon = new QLabel(" ");
    *imgZoneEnvIcon = imgZoneEnvIcon->scaled(32,32,Qt::KeepAspectRatio);
    lblZoneEnvIcon->setPixmap(QPixmap::fromImage(*imgZoneEnvIcon));
    lblZoneEnvIcon->resize(32,32);

    lblZoneEnvHeader = new QLabel(zone->name);
    lblZoneEnvData = new QLabel("0F 0%");

    lblZoneEnvHeader->setObjectName("lblZoneEnvHeader");
    lblZoneEnvData->setObjectName("lblZoneEnvData");
    contentLayout->addWidget(lblZoneEnvIcon,0,0,2,2);
    contentLayout->setAlignment(Qt::AlignLeft);

    contentLayout->addWidget(this->lblZoneEnvHeader,0,2, Qt::AlignLeft);
    contentLayout->addWidget(this->lblZoneEnvData,1,2, Qt::AlignLeft);
    topWidget->setLayout(contentLayout);
}
