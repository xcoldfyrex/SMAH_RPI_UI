/*
    Get here from the zone selector. List of funztions for given zone.
*/

#include "w_zonecontainer.h"
#include "w_lightcontrolcontainer.h"
#include "mainwindow.h"
#include "w_scheduledactions.h"

ZoneContainerWidget::ZoneContainerWidget(QWidget *parent) : QWidget(parent)
{

    topWidget = new QWidget;
    contentLayout = new QStackedWidget;
    QBoxLayout *zoneFunctions = new QBoxLayout(QBoxLayout::TopToBottom);;
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *vboxContainer = new QBoxLayout(QBoxLayout::LeftToRight);;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowActions = new QPushButton;
    QPushButton *btnShowOverview = new QPushButton;


    /*
     * outer layout
    */
    topWidget->setLayout(vboxContainer);
    vboxContainer->addLayout(mainLayout);
    vboxContainer->addLayout(zoneFunctions);

    /*
     * panel container header
     */
    zoneContainerHeader = new ZoneContainerHeaderWidget(this);
    mainLayout->addWidget(zoneContainerHeader->topWidget);


    /*
     * panel container
    */
    contentLayout->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(contentLayout);
    mainLayout->setStretchFactor(contentLayout,0);


    /*
     * panel container widgets(left panel)
    */
    LightControlContainerWidget *lightControlWidget = new LightControlContainerWidget(this);
    ScheduledActionsWidget *scheduledActionsWidget = new ScheduledActionsWidget(this);

    presetChooserWidget = new PresetChooser(this);
    presetChooserWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    zoneOverViewWidget = new ZoneOverviewWidget(this);
    contentLayout->addWidget(zoneOverViewWidget->topWidget);
    contentLayout->addWidget(lightControlWidget->topWidget);
    contentLayout->addWidget(presetChooserWidget->topWidget);
    contentLayout->addWidget(scheduledActionsWidget->topWidget);
    contentLayout->setCurrentIndex(0);

    /*
     * zone functions(right panel)
    */
    QSpacerItem *spacer2 = new QSpacerItem(1,1);
    btnShowLights->setObjectName("btnShowLights");
    btnShowPower->setObjectName("btnShowPower");
    btnShowActions->setObjectName("btnShowActions");
    btnShowOverview->setObjectName("btnMainInfo");

    zoneFunctions->addWidget(btnShowLights,0);
    zoneFunctions->addWidget(btnShowPower,0);
    zoneFunctions->addWidget(btnShowActions,0);
    zoneFunctions->addSpacerItem(spacer2);
    zoneFunctions->addStretch(0);
    zoneFunctions->addWidget(btnShowOverview);
    zoneFunctions->setContentsMargins(10,10,10,10);

    connect(btnShowLights,SIGNAL(clicked()),this,SLOT(showLightContainer()));
    connect(btnShowActions,SIGNAL(clicked()),this,SLOT(showActions()));
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

void ZoneContainerWidget::showActions() {
    contentLayout->setCurrentIndex(3);
}
