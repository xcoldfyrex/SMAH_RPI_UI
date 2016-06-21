#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>

#include "w_zonechooser.h"

extern QList<Zone> *gZoneList;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{

    //qRegisterMetaType("Zone");

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    this->myParent = dynamic_cast<MainWindow*>(parent);


    int gridLoc = 0;
    int row = 0;


}

void ZoneChooserWidget::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void ZoneChooserWidget::addZoneButton(Zone zone)
{
    qDebug() << "ADDING ZONE";
    QPushButton *zonelabel = new QPushButton(zone.name);
    QSignalMapper* signalMapper = new QSignalMapper(this);

    signalMapper->setMapping(zonelabel,zone.id);
    connect(zonelabel,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
    connect(myParent,SIGNAL(zoneChanged(Zone)), myParent->zoneContainer->zoneOverViewWidget,SLOT(switchZone(Zone)));
    contentLayout->addWidget(zonelabel,0 /*gridLoc*/,0 /*row*/,1,1, Qt::AlignVCenter);

}
