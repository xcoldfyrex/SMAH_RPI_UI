/*
    Get here from the zone selector. List of funztions for given zone.
*/

#include "w_zonecontainer.h"
#include "w_lightcontrolcontainer.h"
#include "w_mainwindow.h"
#include <QDebug>
#include <QStackedLayout>
#include <QPushButton>

ZoneContainerWidget::ZoneContainerWidget(QWidget *parent) : QWidget(parent)
{

    topWidget = new QWidget;
    contentLayout = new QStackedLayout;
    QBoxLayout *zoneFunctions = new QBoxLayout(QBoxLayout::TopToBottom);;
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *vboxContainer = new QBoxLayout(QBoxLayout::LeftToRight);;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowOverview = new QPushButton;


    /*
     * outer layout
    */
    topWidget->setLayout(vboxContainer);
    vboxContainer->addLayout(mainLayout);
    vboxContainer->addLayout(zoneFunctions);

    /*
     * panel container
    */
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch(1);

    /*
     * create node widgets(left panel)
    */
    LightControlContainerWidget *lightControlWidget = new LightControlContainerWidget(this);
    presetChooserWidget = new PresetChooser(this);
    zoneOverViewWidget = new ZoneOverviewWidget(this);
    contentLayout->addWidget(zoneOverViewWidget->topWidget);
    contentLayout->addWidget(lightControlWidget->topWidget);
    contentLayout->addWidget(presetChooserWidget->topWidget);
    contentLayout->setCurrentIndex(0);

    /*
     * zone functions(right panel)
    */
    QSpacerItem *spacer2 = new QSpacerItem(1,1);
    btnShowLights->setObjectName("btnShowLights");
    btnShowPower->setObjectName("btnShowPower");
    btnShowOverview->setObjectName("btnhome");

    zoneFunctions->addWidget(btnShowLights,0);
    zoneFunctions->addWidget(btnShowPower,0);
    zoneFunctions->addSpacerItem(spacer2);
    zoneFunctions->addStretch(1);
    zoneFunctions->addWidget(btnShowOverview);
    zoneFunctions->setContentsMargins(10,10,10,10);

    connect(btnShowLights,SIGNAL(clicked()),this,SLOT(showLightContainer()));
    connect(btnShowOverview,SIGNAL(clicked()),this,SLOT(showOverview()));

}

void ZoneContainerWidget::showOverview() {
    contentLayout->setCurrentIndex(0);
}

void ZoneContainerWidget::showLightContainer() {
    contentLayout->setCurrentIndex(1);
}

void ZoneContainerWidget::showPresetChooser() {
    contentLayout->setCurrentIndex(2);
}
