#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>

#include "w_zonechooser.h"

extern QList<Zone> *gZoneList;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    this->myParent = dynamic_cast<MainWindow*>(parent);
}

void ZoneChooserWidget::addZoneButton(Zone *zone)
{
    QPushButton *zonelabel = new QPushButton(zone->name);
    QSignalMapper* signalMapper = new QSignalMapper(this);

    signalMapper->setMapping(zonelabel,zone->id);
    connect(zonelabel,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
    connect(myParent,SIGNAL(zoneChanged(Zone)), myParent->zoneContainer->zoneOverViewWidget,SLOT(switchZone(Zone)));
    contentLayout->addWidget(zonelabel,zone->id /*gridLoc*/, 0, 1, 1, Qt::AlignVCenter);
}
