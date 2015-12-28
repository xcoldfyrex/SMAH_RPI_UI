#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include "zone.h"

#include <QDebug>
#include <QSignalMapper>

extern QList<Zone> *gZoneList;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);


    int gridLoc = 0;
    int row = 0;

    MainWindow* myParent = dynamic_cast<MainWindow*>(parent);

    foreach (Zone zone, *gZoneList) {
        QPushButton *zonelabel = new QPushButton(zone.name);
        QSignalMapper* signalMapper = new QSignalMapper(this);

        signalMapper->setMapping(zonelabel,zone.id);
        connect(zonelabel,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(int)),myParent,SLOT(showZone(int)));
        connect(myParent,SIGNAL(zoneChanged(Zone)), myParent->zoneContainer->zoneOverViewWidget,SLOT(switchZone(Zone)));
        contentLayout->addWidget(zonelabel,gridLoc,row,1,1, Qt::AlignVCenter);
        gridLoc++;
        if (gridLoc == 4) {
            row++;
            gridLoc = 0;
        }
    }
}

void ZoneChooserWidget::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
