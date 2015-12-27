/*
    Get here from the zone selector. List of funztions for given zone.
*/

#include "w_zonecontainer.h"
#include "w_lightcontrolcontainer.h"
#include "w_zoneoverview.h"
#include "w_mainwindow.h"
#include <QDebug>
#include <QStackedLayout>
#include <QPushButton>

ZoneContainerWidget::ZoneContainerWidget(QWidget *parent) : QWidget(parent)
{

    topWidget = new QWidget;
    QStackedLayout *contentLayout = new QStackedLayout;
    QBoxLayout *zoneFunctions = new QBoxLayout(QBoxLayout::TopToBottom);;
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *vboxContainer = new QBoxLayout(QBoxLayout::LeftToRight);;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;

    //outer layout
    //
    topWidget->setLayout(vboxContainer);
    vboxContainer->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Fixed,QSizePolicy::Expanding));
    vboxContainer->addLayout(mainLayout);
    vboxContainer->addLayout(zoneFunctions);

    //panel container
    //
    mainLayout->addLayout(contentLayout);

    //create node widgets(left panel)
    //
    LightControlContainerWidget *lightControlWidget = new LightControlContainerWidget(this);
    ZoneOverviewWidget *zoneOverViewWidget = new ZoneOverviewWidget(this);
    contentLayout->addWidget(zoneOverViewWidget->topWidget);
    //contentLayout->addWidget(lightControlWidget->topWidget);
    contentLayout->setAlignment(Qt::AlignTop);

    //zone functions(right panel)
    //
    QSpacerItem *spacer2 = new QSpacerItem(1,1);
    btnShowLights->setObjectName("btnShowLights");
    btnShowPower->setObjectName("btnShowPower");

    zoneFunctions->addWidget(btnShowLights,0);
    zoneFunctions->addWidget(btnShowPower,0);
    zoneFunctions->addSpacerItem(spacer2);
    zoneFunctions->addStretch(1);

    zoneFunctions->setContentsMargins(10,10,10,10);

    MainWindow* myParent = dynamic_cast<MainWindow*>(parent);

    //myParent->contentLayout->setCurrentIndex(1);
}

