#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QPushButton>

#include "w_presetchooser.h"
#include "w_powercontrol.h"
#include "w_zoneoverview.h"
#include "w_zone_lights.h"
#include "zone2.h"

class PresetChooser;

class ZoneOverviewWidget;

//class ZoneLightsWidget;

//class Zone;

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(Zone zone);
    ZoneContainerWidget() {}
    QWidget *topWidget;
    QStackedWidget *contentLayout;

private:
    ZoneLightsWidget *zoneLightsWidget;
    ZoneOverviewWidget *zoneOverViewWidget;
    PresetChooser *presetChooserWidget;
    PowerControlWidget *powerControlWidget;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowActions = new QPushButton;
    QListWidget *zoneButtons = new QListWidget(this);

private slots:
    void showLightContainer();
    void showPowerControl();
    void showOverview();
    void showActions();
    void buttonListClicked();
};

#endif // ZONECONTAINERWIDGET_H
