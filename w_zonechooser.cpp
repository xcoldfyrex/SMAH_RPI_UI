#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include "zone.h"
#include <QDebug>
#include <QSignalMapper>

extern QList<Zone> *zoneList;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);


    int gridLoc = 0;
    int row = 0;
    foreach (Zone zone, *zoneList) {
        QPushButton *zonelabel = new QPushButton(zone.name);
        MainWindow* myParent = dynamic_cast<MainWindow*>(parent);
        QSignalMapper* signalMapper = new QSignalMapper(this);
        signalMapper->setMapping(zonelabel,zone.name);
        connect(zonelabel,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(QString)),myParent,SLOT(showZone(QString)));

        contentLayout->addWidget(zonelabel,gridLoc,row,1,1, Qt::AlignVCenter);
        qDebug() << "ZONE " << zone.name;
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
