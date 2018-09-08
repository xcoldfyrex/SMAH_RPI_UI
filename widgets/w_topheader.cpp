#include <QTimer>
#include <QTime>

#include "w_topheader.h"
#include "mainwindow.h"

TopHeaderWidget::TopHeaderWidget(QWidget *parent, const char *name) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);
    this->lblClock = new QLabel("");
    this->lblDate = new QLabel("");
    this->lblPath = new QLabel(name);
    this->btnHome = new QPushButton("");
    this->btnInfo = new QPushButton("");
    this->spcHeader = new QSpacerItem(1,1);
    this->topWidgetLayout->addWidget(lblClock);
    this->topWidgetLayout->addStretch(1);
    this->topWidgetLayout->addSpacerItem(spcHeader);
    topWidgetLayout->addWidget(btnInfo);
    topWidgetLayout->addWidget(btnHome);

    topWidget->setFixedHeight(75);
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
    QString datetime = QTime::currentTime().toString("hh:mm:ss") + "\n" + QDate::currentDate().toString("ddd, MMMM dd yyyy");
    this->lblClock->setText(datetime);
}
