/*
    Get here from the zone selector. List of funztions for given zone.
*/

#include "w_zonecontainer.h"
//#include "w_lightcontrolcontainer.h"
//#include "w_scheduledactions.h"

ZoneContainerWidget::ZoneContainerWidget(Zone zone)
{

    topWidget = new QWidget;
    contentLayout = new QStackedWidget;
    //QBoxLayout *zoneFunctions = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *vboxContainer = new QBoxLayout(QBoxLayout::TopToBottom);
    QWidget *bottomPanelWidget = new QWidget;
    QWidget *zonePanelWidget = new QWidget;
    //QWidget *devicePanelWidget = new QWidget;
    QWidget *zoneMainWidget = new QWidget;
    QHBoxLayout *bottomLayout = new QHBoxLayout(bottomPanelWidget);
    QVBoxLayout *zoneMainLayout = new QVBoxLayout(zoneMainWidget);

    QHBoxLayout *zoneFunctionLayout = new QHBoxLayout(zonePanelWidget);
    //QHBoxLayout *devicePanelLayout = new QHBoxLayout(devicePanelWidget);
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowActions = new QPushButton;


    /*
     * outer layout
    */
    topWidget->setLayout(vboxContainer);
    vboxContainer->addLayout(mainLayout);
    vboxContainer->addWidget(bottomPanelWidget);
    vboxContainer->setContentsMargins(0,0,0,0);



    /*
     * panel container
    */
    contentLayout->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    mainLayout->addWidget(contentLayout);
    //mainLayout->setStretchFactor(contentLayout,0);

    /*
     * device/function combined layout
     */
    zoneMainLayout->addWidget(zonePanelWidget);

    /*
     * panel container widgets(pages)
    */
    //LightControlContainerWidget *lightControlWidget = new LightControlContainerWidget(zone, this);
    //ScheduledActionsWidget *scheduledActionsWidget = new ScheduledActionsWidget(this);
    this->powerControlWidget = new PowerControlWidget(zone, this);
    this->zoneLightsWidget = new ZoneLightsWidget(zone, this);

    //presetChooserWidget = new PresetChooser(zone, this);
    //presetChooserWidget->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    zoneOverViewWidget = new ZoneOverviewWidget(zone, this);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(zoneMainWidget);
    contentLayout->addWidget(zoneLightsWidget->topWidget);
    contentLayout->addWidget(zoneOverViewWidget->topWidget);
    //contentLayout->addWidget(lightControlWidget->topWidget);
    //contentLayout->addWidget(presetChooserWidget->topWidget);
    //contentLayout->addWidget(scheduledActionsWidget->topWidget);
    contentLayout->addWidget(powerControlWidget->topWidget);
    contentLayout->setCurrentIndex(0);

    /*
     * zone functions bar
    */

    zoneButtons = new QListWidget(this);
    QSpacerItem *verticalSpacer = new QSpacerItem(0,500,QSizePolicy::Expanding, QSizePolicy::Expanding);
    zoneFunctionLayout->addItem(verticalSpacer);
    QListWidgetItem *itemLights = new QListWidgetItem("Light Controls");
    QListWidgetItem *itemPower = new QListWidgetItem("Power Controls");
    QListWidgetItem *itemEvents = new QListWidgetItem("Scheduled Events");
    itemLights->setData(Qt::UserRole,1);
    itemPower->setData(Qt::UserRole,2);
    itemEvents->setData(Qt::UserRole,3);
    zoneButtons->addItem(itemLights);
    zoneButtons->addItem(itemPower);
    zoneButtons->addItem(itemEvents);

    connect(zoneButtons,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(buttonListClicked()));
    //zoneButtons->setItemWidget(itemLights,btnShowLights);

    zonePanelWidget->setObjectName("zoneFunctionsWidget");
    btnShowLights->setObjectName("btnShowLights");
    btnShowPower->setObjectName("btnShowPower");
    btnShowActions->setObjectName("btnShowActions");
    zoneFunctionLayout->addWidget(zoneButtons);

    //zoneFunctionLayout->addWidget(btnShowLights,0);
    //zoneFunctionLayout->addWidget(btnShowPower,0);
    //zoneFunctionLayout->addWidget(btnShowActions,0);

    zoneFunctionLayout->setContentsMargins(10,10,10,10);
    zoneFunctionLayout->setAlignment(Qt::AlignTop);
    //zoneFunctionLayout->addStretch(1);

    connect(btnShowLights,SIGNAL(clicked()),this,SLOT(showLightContainer()));
    connect(btnShowActions,SIGNAL(clicked()),this,SLOT(showActions()));
    connect(btnShowPower,SIGNAL(clicked()),this,SLOT(showPowerControl()));

    /*
     * device functions bar
    */
    //devicePanelWidget->setObjectName("devicePanelWidget");
    //btnShowActions->setObjectName("btnShowActions");
    //foreach (RPIDevice device, zone.getDeviceList())
    //{
    //    QPushButton *btnDevice = new QPushButton(device.getName());
    //    devicePanelLayout->addWidget(btnDevice,0);
    //}/
    //devicePanelLayout->setContentsMargins(10,10,10,10);
    //devicePanelLayout->setAlignment(Qt::AlignTop);
    //devicePanelLayout->addStretch(1);

    /*
     * bottom status bar
    */
    QLabel *lblZone = new QLabel(zone.getName());
    QPushButton *btnShowOverview = new QPushButton("Zone Functions");
    bottomLayout->addWidget(btnShowOverview);
    bottomLayout->addStretch(1);
    bottomLayout->addWidget(lblZone);
    bottomPanelWidget->setFixedHeight(50);
    bottomPanelWidget->setObjectName("bottomPanelWidget");
    connect(btnShowOverview,SIGNAL(clicked()),this,SLOT(showOverview()));
}

void ZoneContainerWidget::showOverview()
{
    contentLayout->setCurrentIndex(0);
}

void ZoneContainerWidget::showLightContainer()
{
    contentLayout->setCurrentIndex(1);
}


void ZoneContainerWidget::showActions()
{
    contentLayout->setCurrentIndex(3);
}

void ZoneContainerWidget::showPowerControl()
{
    contentLayout->setCurrentWidget(this->powerControlWidget->topWidget);
}

void ZoneContainerWidget::buttonListClicked()
{
    contentLayout->setCurrentIndex(zoneButtons->currentItem()->data(Qt::UserRole).toInt());
}
