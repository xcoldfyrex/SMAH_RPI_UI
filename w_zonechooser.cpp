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
    QPushButton *zonelabel = new QPushButton(zone->name);
    QSignalMapper *signalMapper = new QSignalMapper(this);


    if (zone->hasEnviro) {
        ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this,zone);
        zenv->topWidget->setObjectName("zoneEnv");
        contentLayout->addWidget(zenv->topWidget,envZones, 0, 1, 1, Qt::AlignLeft);
    }
    if (zone->hasLedRGB) {
        signalMapper->setMapping(zonelabel,zone->id);
        connect(myParent,SIGNAL(zoneChanged(Zone)), myParent->zoneContainer->zoneContainerHeader,SLOT(switchZone(Zone)));
        connect(zonelabel,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
        contentLayout->addWidget(zonelabel,controlZones  /*gridLoc*/, 1, 1, 1, Qt::AlignVCenter);
    }
}
