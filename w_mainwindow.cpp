/*
 Create the first widget you see when opening the application

*/

#include "w_mainwindow.h"
#include "w_zonechooser.h"
#include "w_lightcontrolcontainer.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSignalMapper>

extern Zone *gActiveZone;
extern QList<Zone*> *gZoneList;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

    this->setObjectName("MainWindow");
    this->setStyle(QApplication::style());
    this->setAutoFillBackground(true);
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
    this->repaint();

    //create header template
    TopHeaderWidget *hcheader = new TopHeaderWidget(this,"Main Menu");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->contentLayout = new QStackedLayout;

    //create node widgets
    zoneContainer = new ZoneContainerWidget(this);
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);

    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(zoneContainer->topWidget);

    setLayout(mainLayout);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MainWindow::showZoneChooser() {
    contentLayout->setCurrentIndex(0);
}

void MainWindow::showZone(int zone) {
    /* TODO: ADD ERROR HANDLING IF ZONELIST IS NULL */

    zone--;
    emit zoneChanged(*gZoneList->at(zone));
    contentLayout->setCurrentIndex(1);
}

