#include "w_zoneenvironment.h"
#include "math.h"

extern QMap<int, QList<int>> *gEnvironmentMap;

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

    lblZoneEnvHeader = new QLabel(zone->name);
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
    QList<int> envData = gEnvironmentMap->value(this->zone->id);
    float temp = ceilf(rawVoltage(envData.value(0) * 100) * 100) / 100;
    float rh = rawVoltage((envData.value(1) / 5) - 0.16) / 0.0062;
    float trh = ceilf(rh / (1.093 - 0.0012 * temp) * 100) / 100;

    lblZoneEnvData->setText(QString::number(temp) + " F\n" + QString::number(trh) + " %");
}

float ZoneEnvironmentPanel::rawVoltage(int reading)
{
    float ref = 4.95;
    return (reading * ref) / float(4096);
}
