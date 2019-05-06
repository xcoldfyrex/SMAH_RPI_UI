#include "w_zonefunctionsbasewidget.h"
#include "w_zonechooser.h"

extern QMap<QString, Zone> gZoneMap;

ZoneFunctionsBaseWidget::ZoneFunctionsBaseWidget(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);

    this->mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);
    this->contentLayout = new QStackedLayout();
    this->zoneContainerMap = new QMap<QString, ZoneContainerWidget*>;

    topWidget->setLayout(mainLayout);

    foreach (Zone zone, gZoneMap) {
        ZoneContainerWidget *zcw = new ZoneContainerWidget(zone);
        this->zoneContainerMap->insert(zone.getName(),zcw);
        contentLayout->addWidget(zcw->topWidget);
    }

    mainLayout->addWidget(zoneChooser->topWidget);
    mainLayout->addLayout(contentLayout);
    contentLayout->setCurrentIndex(0);
}

void ZoneFunctionsBaseWidget::showZone(QString zone) {
    /* TODO: ADD ERROR HANDLING IF ZONELIST IS NULL */
    //emit zoneChanged(zone);
    contentLayout->setCurrentWidget(this->getZoneContainer(zone)->topWidget);
}
