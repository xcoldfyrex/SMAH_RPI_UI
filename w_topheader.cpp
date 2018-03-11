#include <QTimer>
#include <QTime>

#include "w_topheader.h"
#include "mainwindow.h"

TopHeaderWidget::TopHeaderWidget(QWidget *parent, const char *name) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);
    this->lblClock = new QLabel("");
    this->lblPath = new QLabel(name);
    this->btnHome = new QPushButton("Zones");
    this->btnInfo = new QPushButton("System");
    this->spcHeader = new QSpacerItem(1,1);
    this->topWidgetLayout->addWidget(lblClock);
    this->topWidgetLayout->addStretch(1);
    this->topWidgetLayout->addSpacerItem(spcHeader);
    topWidgetLayout->addWidget(btnInfo);
    topWidgetLayout->addWidget(btnHome);

    topWidget->setFixedHeight(50);
    btnHome->setObjectName("btnTopZones");
    btnInfo->setObjectName("btnTopSystem");
    topWidget->setObjectName("header");
    lblClock->setObjectName("clock");
    topWidget->setAutoFillBackground(true);

    MainWindow* myParent = dynamic_cast<MainWindow*>(parent);
    connect(btnHome,SIGNAL(clicked(bool)),myParent,SLOT(showZoneChooser()));
    connect(btnInfo,SIGNAL(clicked(bool)),myParent,SLOT(showSystemWidget()));

    //timer for clock
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
}

void TopHeaderWidget::showTime()
{
    this->lblClock->setText(QTime::currentTime().toString("hh:mm:ss "));
}
