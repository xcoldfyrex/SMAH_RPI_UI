#include <QTimer>
#include <QTime>
#include <time.h>
#include <QDebug>
#include <QDateTime>

#include "w_topheader.h"
#include "mainwindow.h"
#include "sunriseset.h"


TopHeaderWidget::TopHeaderWidget(QWidget *parent, const char *name) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);
    this->lblClock = new QLabel("");
    this->lblDate = new QLabel("");
    this->lblSunrise = new QLabel("");
    this->lblSunset = new QLabel("");
    this->lblPath = new QLabel(name);
    this->btnHome = new QPushButton("");
    this->btnInfo = new QPushButton("");
    this->spcHeader = new QSpacerItem(1,1);
    QGridLayout *grid = new QGridLayout();
    this->topWidgetLayout->addLayout(grid);
    grid->addWidget(lblClock,0,0);
    grid->addWidget(lblDate,1,0);
    grid->addWidget(new QLabel("           "),0,1);
    grid->addWidget(new QLabel("      "),2,0,1,3);
    grid->addWidget(lblSunrise,0,5);
    grid->addWidget(lblSunset,1,5);
    grid->setContentsMargins(0,0,0,0);
    this->topWidgetLayout->addStretch(1);
    this->topWidgetLayout->addSpacerItem(spcHeader);
    topWidgetLayout->addWidget(btnInfo);
    topWidgetLayout->addWidget(btnHome);
    topWidgetLayout->setContentsMargins(0,0,0,0);
    topWidget->setFixedHeight(75);
    grid->setObjectName("headerGrid");
    btnHome->setObjectName("btnTopZones");
    btnInfo->setObjectName("btnTopSystem");
    topWidget->setObjectName("header");
    lblClock->setObjectName("clock");
    lblDate->setObjectName("date");

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
    this->lblClock->setText(QTime::currentTime().toString("hh:mm:ss"));
    this->lblDate->setText(QDate::currentDate().toString("ddd, MMMM dd yyyy"));

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char buf[16];
    strftime(buf, sizeof(buf), "%z", &tm);
    int tz = ::atoi(buf)/100;

    bool ok;
    SunSet sun;
    sun.setPosition(47.530690,122.607160,tz);
    QDateTime dt = QDateTime::currentDateTime();
    sun.setCurrentDate(dt.toString("yyyy").toInt(&ok), dt.toString("M").toInt(&ok),dt.toString("d").toInt(&ok));
    int sunrise;
    int sunset;
    sunrise = sun.calcSunrise();
    sunset = sun.calcSunset();
    QString sr = QString::number(sunrise/60).rightJustified(2, '0') + ":" + QString::number(abs(sunrise%60)).rightJustified(2, '0');
    QString sd = QString::number(sunset/60).rightJustified(2, '0') + ":" + QString::number(abs(sunset%60)).rightJustified(2, '0');
    this->lblSunrise->setText("Sunrise:\t" + sr);
    this->lblSunset->setText("Sunset:\t" + sd);
}
