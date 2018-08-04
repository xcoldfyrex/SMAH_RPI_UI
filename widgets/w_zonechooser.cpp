#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>

#include "w_zonechooser.h"
#include "w_zoneenvironment.h"

extern QMap<QString, Zone> gZoneMap;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{
    this->topWidget = new QWidget;
    zoneList = new QListWidget(this);
    QSpacerItem *verticalSpacer = new QSpacerItem(0,2000,QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->contentLayout = new QHBoxLayout(topWidget);
    contentLayout->addItem(verticalSpacer);
    contentLayout->addWidget(zoneList);
    this->myParent = dynamic_cast<MainWindow*>(parent);
    foreach (Zone zone, gZoneMap) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant data(zone.getName());
        item->setData(Qt::UserRole, data);
        item->setText(zone.getName());
        zoneList->addItem(item);
        offset++;

        /*
    if (zone->getEnvironmentCapability()) {
        ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this, zone);
        zenv->topWidget->setObjectName("zoneEnv");
        contentLayout->addWidget(zenv->topWidget,envZones, 0, 1, 1, Qt::AlignLeft);
    }
    if (zone->getLedColorCapability() || zone->getLedWhiteCapability() || zone->getPowerCapability()) {
        signalMapper->setMapping(zone->zoneSelector,zone->getId());
        connect(zone->zoneSelector,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
        contentLayout->addWidget(zone->zoneSelector,controlZones  /*gridLoc, 1, 1, 1, Qt::AlignVCenter);
    }
    */

    }
    connect(zoneList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getZoneFromSelected()));
}

void ZoneChooserWidget::getZoneFromSelected()
{
    myParent->showZone(this->zoneList->currentItem()->data(Qt::UserRole).toString());
}

