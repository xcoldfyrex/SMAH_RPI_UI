#include <QTimer>
#include <QTime>
#include <QGraphicsEffect>

#include "w_screensaver.h"

ScreenSaverWidget::ScreenSaverWidget(QWidget *parent) : QWidget(parent)
{
    lblClock = new QLabel("");
    this->topWidget = new QWidget;
    this->setCursor(Qt::BlankCursor);
    topWidget->setObjectName("saverBackground");
    lblClock->setObjectName("lblSaverClock");
    lblClock->setAlignment(Qt::AlignLeft);
    this->topWidgetLayout = new QHBoxLayout(topWidget);
    topWidgetLayout->addWidget(lblClock);
    //timer for clock
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    QGraphicsDropShadowEffect* eff = new QGraphicsDropShadowEffect(this);
    eff->setBlurRadius(5);
    eff->setColor(QColor("FFFFFF"));
    lblClock->setGraphicsEffect(eff);
}

void ScreenSaverWidget::showTime()
{
    this->lblClock->setText(QTime::currentTime().toString("hh:mm:ss"));
}


