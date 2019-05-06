#include <QTimer>
#include <QTime>
#include <zone.h>
#include "w_screensaver.h"
#include "w_zoneenvironment.h"

extern QMap<QString, Zone> gZoneMap;

ScreenSaverWidget::ScreenSaverWidget(QWidget *parent) : QWidget(parent)
{
    lblClock = new QLabel("");
    this->topWidget = new QWidget;
    this->setCursor(Qt::BlankCursor);
    topWidget->setObjectName("saverBackground");
    lblClock->setObjectName("lblSaverClock");
    lblClock->setAlignment(Qt::AlignLeft);
    QGridLayout *topWidgetLayout = new QGridLayout(topWidget);
    topWidgetLayout->addWidget(lblClock,0,0);
    //timer for clock
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    foreach (Zone zone, gZoneMap) {
        if (zone.getName() == "Outside") {
            if (zone.getSensorList().size() != 0)
            {
                ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this, zone.getSensorList().value("Outside"), true);
                zenv->topWidget->setObjectName("lblSaverTemp");
                topWidgetLayout->addWidget(zenv->topWidget,1,0);
            }
        }
    }
}

void ScreenSaverWidget::showTime()
{
    this->lblClock->setText(QTime::currentTime().toString("hh:mm:ss"));
}


