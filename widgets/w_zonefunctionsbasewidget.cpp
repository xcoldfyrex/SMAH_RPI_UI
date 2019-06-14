#include "w_zonefunctionsbasewidget.h"
#include "w_zonechooser.h"

extern QMap<QString, Zone> gZoneMap;

ZoneFunctionsBaseWidget::ZoneFunctionsBaseWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget(parent);
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);
    zoneChooser->setObjectName("ZoneChooserWidget");
    this->mainLayout = new QHBoxLayout();
    mainLayout->addWidget(zoneChooser->topWidget);
    //this->setFixedSize(1280,800);
    this->contentLayout = new QStackedLayout(mainLayout);
    contentLayout->setContentsMargins(0,0,0,0);
    mainLayout->setContentsMargins(0,0,0,0);
    this->zoneContainerMap = new QMap<QString, ZoneContainerWidget*>;
    topWidget->setLayout(mainLayout);

    foreach (Zone zone, gZoneMap) {
        ZoneContainerWidget *zcw = new ZoneContainerWidget(zone);
        this->zoneContainerMap->insert(zone.getName(),zcw);
        contentLayout->addWidget(zcw->topWidget);
    }

    //mainLayout->addLayout(contentLayout);
    contentLayout->setCurrentIndex(0);
}

void ZoneFunctionsBaseWidget::showZone(QString zone) {
    /* TODO: ADD ERROR HANDLING IF ZONELIST IS NULL */
    //emit zoneChanged(zone);
    contentLayout->setCurrentWidget(this->getZoneContainer(zone)->topWidget);
}

void ZoneFunctionsBaseWidget::paintEvent(QPaintEvent *)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
