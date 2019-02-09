#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>
#include <QSizePolicy>

#include "w_zonechooser.h"
#include "w_zoneenvironment.h"

extern QMap<QString, Zone> gZoneMap;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{
    this->topWidget = new QWidget;
    zoneList = new QListWidget(this);
    zoneList->setObjectName("zoneList");
    this->contentLayout = new QHBoxLayout(topWidget);
    this->myParent = dynamic_cast<MainWindow*>(parent);
    foreach (Zone zone, gZoneMap) {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant data(zone.getName());
        item->setData(Qt::UserRole, data);
        item->setText("> " + zone.getName());
        zoneList->addItem(item);
        offset++;
        if (zone.getSensorList().size() != 0)
        {
            ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this, zone);
            zenv->topWidget->setObjectName("zoneEnv");
            contentLayout->addWidget(zenv->topWidget, Qt::AlignLeft);
        }

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

    contentLayout->addWidget(zoneList,1, Qt::AlignRight);
    zoneList->setMinimumWidth(zoneList->sizeHintForColumn(0) + 20);
    zoneList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(zoneList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getZoneFromSelected()));
}

void ZoneChooserWidget::getZoneFromSelected()
{
    myParent->showZone(this->zoneList->currentItem()->data(Qt::UserRole).toString());
}

