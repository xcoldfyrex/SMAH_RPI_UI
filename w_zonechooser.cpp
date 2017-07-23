#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>

#include "w_zonechooser.h"
#include "w_zoneenvironment.h"

extern QList<Zone> *gZoneList;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    this->myParent = dynamic_cast<MainWindow*>(parent);
}

void ZoneChooserWidget::addZoneButton(Zone *zone, int envZones, int controlZones)
{
    QSignalMapper *signalMapper = new QSignalMapper(this);
    zone->zoneSelector->setEnabled(false);


    if (zone->hasEnviro) {
        ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this, zone);
        zenv->topWidget->setObjectName("zoneEnv");
        contentLayout->addWidget(zenv->topWidget,envZones, 0, 1, 1, Qt::AlignLeft);
    }
    if (zone->hasLedRGB || zone->hasLedWhite || zone->hasPower) {
        signalMapper->setMapping(zone->zoneSelector,zone->id);
        //connect(myParent,SIGNAL(zoneChanged(Zone)), myParent->zoneContainer->zoneContainerHeader,SLOT(switchZone(Zone)));
        //connect(myParent,SIGNAL(zoneChanged(Zone)), myParent,SLOT(showZone(Zone)));
        connect(zone->zoneSelector,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
        contentLayout->addWidget(zone->zoneSelector,controlZones  /*gridLoc*/, 1, 1, 1, Qt::AlignVCenter);
    }
}
