#include "w_topheader.h"
#include "w_mainwindow.h"

TopHeaderWidget::TopHeaderWidget(QWidget *parent, const char *name) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->topWidgetLayout = new QHBoxLayout(topWidget);
    this->lblClock = new QLabel("CLOCK");
    this->lblPath = new QLabel(name);
    this->btnHome = new QPushButton();
    this->spcHeader = new QSpacerItem(1,1);
    this->topWidgetLayout->addWidget(lblClock);
    this->topWidgetLayout->addStretch(1);
    this->topWidgetLayout->addWidget(lblPath);
    this->topWidgetLayout->addSpacerItem(spcHeader);

    this->topWidgetLayout->addWidget(btnHome);
    this->topWidget->setFixedHeight(50);
    this->btnHome->setObjectName("btnhome");
    this->topWidget->setObjectName("header");
    this->lblClock->setObjectName("clock");
    this->lblPath->setObjectName("path");
    this->topWidget->setAutoFillBackground(true);

    MainWindow* myParent = dynamic_cast<MainWindow*>(parent);
    connect(btnHome,SIGNAL(clicked(bool)),myParent,SLOT(showZoneChooser()));
}
