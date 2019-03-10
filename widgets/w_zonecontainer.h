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
#include "zone.h"
#include "qengravedlabel.h"

class PresetChooser;

class ZoneOverviewWidget;

class ZoneLightsWidget;

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
    QEngravedList *zoneButtons = new QEngravedList(this);
    Zone zone;
    QLabel *lblEnvironment;

private slots:
    void showLightContainer();
    void showPowerControl();
    void showOverview();
    void showActions();
    void buttonListClicked();
    void updateEnvironment();
};

#endif // ZONECONTAINERWIDGET_H
