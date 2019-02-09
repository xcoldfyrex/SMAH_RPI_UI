#include <QTimer>
#include <QTime>
#include "w_screensaver.h"

#include <QDebug>

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
}

void ScreenSaverWidget::showTime()
{
    this->lblClock->setText(QTime::currentTime().toString("hh:mm:ss"));
}


