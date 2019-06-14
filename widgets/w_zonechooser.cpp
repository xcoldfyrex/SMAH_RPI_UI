#include <QDebug>
#include <QSignalMapper>
#include <QMetaType>
#include <QSizePolicy>
#include <QGraphicsEffect>

#include "w_zonechooser.h"
#include "w_zoneenvironment.h"

extern QMap<QString, Zone> gZoneMap;
extern QString *activeZone;

ZoneChooserWidget::ZoneChooserWidget(QWidget *parent) :
    QWidget(parent)

{
    this->topWidget = new QWidget;
    zoneList = new QEngravedList(this);
    zoneList->setObjectName("zoneList");
    this->contentLayout = new QVBoxLayout(topWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    QWidget *envWidget = new QWidget(this);
    QGridLayout *envHolder = new QGridLayout(envWidget);
    envHolder->setObjectName("envHolder");
    envWidget->setObjectName("envWidget");

    this->myParent = dynamic_cast<ZoneFunctionsBaseWidget*>(parent);
    int enviroGridOffset = 0;
    foreach (Zone zone, gZoneMap) {

        // right now we only look at lights
        if (zone.getLightList().size() != 0 || zone.getSensorList().size() != 0)
        {
            QListWidgetItem *item = new QListWidgetItem();
            QVariant data(zone.getName());
            item->setData(Qt::UserRole, data);
            item->setText(zone.getName());
            zoneList->addItem(item);
            offset++;
        }        
    }
    QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    envHolder->addItem(verticalSpacer,enviroGridOffset,0);    
    contentLayout->addWidget(zoneList,0, Qt::AlignLeft);
    //contentLayout->addWidget(envWidget,1, Qt::AlignRight);
    zoneList->setMinimumWidth(zoneList->sizeHintForColumn(0) + 20);
    zoneList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(zoneList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getZoneFromSelected()));
}

void ZoneChooserWidget::getZoneFromSelected()
{
    myParent->showZone(this->zoneList->currentItem()->data(Qt::UserRole).toString());
}

