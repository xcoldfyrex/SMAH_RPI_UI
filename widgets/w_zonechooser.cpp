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
    this->contentLayout = new QHBoxLayout(topWidget);
    QWidget *envWidget = new QWidget(this);
    QGridLayout *envHolder = new QGridLayout(envWidget);

    this->myParent = dynamic_cast<MainWindow*>(parent);
    int enviroGridOffset = 0;
    foreach (Zone zone, gZoneMap) {

        // right now we only look at lights
        if (zone.getLightList().size() != 0)
        {
            QListWidgetItem *item = new QListWidgetItem();
            QVariant data(zone.getName());
            item->setData(Qt::UserRole, data);
            item->setText("> " + zone.getName());
            zoneList->addItem(item);
            offset++;
        }
        if (zone.getSensorList().size() != 0)
        {
            ZoneEnvironmentPanel *zenv = new ZoneEnvironmentPanel(this, zone);
            zenv->topWidget->setObjectName("zoneEnv");
            zenv->setMinimumWidth(800);
            zenv->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            envHolder->addWidget(zenv->topWidget, enviroGridOffset, 0, Qt::AlignLeft);
            enviroGridOffset++;
        }
    }
    QSpacerItem *verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    envHolder->addItem(verticalSpacer,enviroGridOffset,0);
    contentLayout->addWidget(envWidget,0, Qt::AlignLeft);
    contentLayout->addWidget(zoneList,1, Qt::AlignRight);
    zoneList->setMinimumWidth(zoneList->sizeHintForColumn(0) + 20);
    zoneList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(zoneList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(getZoneFromSelected()));
}

void ZoneChooserWidget::getZoneFromSelected()
{
    myParent->showZone(this->zoneList->currentItem()->data(Qt::UserRole).toString());
}

