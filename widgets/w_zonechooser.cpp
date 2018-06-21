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
    this->contentLayout = new QGridLayout(topWidget);
    this->myParent = dynamic_cast<MainWindow*>(parent);
    foreach (Zone zone, gZoneMap) {
        QSignalMapper *signalMapper = new QSignalMapper(this);
        QPushButton *btn = new QPushButton(zone.getName());
        signalMapper->setMapping(btn,zone.getName());
        connect(btn,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(QString)),myParent,SLOT(showZone(QString)));
        contentLayout->addWidget(btn, this->offset  /*gridLoc*/, 1, 1, 1, Qt::AlignVCenter);
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

}

