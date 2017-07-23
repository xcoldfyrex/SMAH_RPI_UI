#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "w_presetchooser.h"
#include "w_powercontrol.h"
#include "w_zoneoverview.h"
#include "w_zonecontainerheader.h"
#include "zone.h"


class PowerControlWidget;

class PresetChooser;

class ZoneOverviewWidget;

class ZoneContainerHeaderWidget;

class Zone;


class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    ZoneContainerWidget(Zone *zone);
    QWidget *topWidget;
    QStackedWidget *contentLayout;

private:
    ZoneOverviewWidget *zoneOverViewWidget;
    PresetChooser *presetChooserWidget;
    ZoneContainerHeaderWidget *zoneContainerHeader;
    PowerControlWidget *powerControlWidget;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowActions = new QPushButton;

private slots:
    void showLightContainer();
    void showPowerControl();
    void showOverview();
    void showPresetChooser();
    void showActions();
};

#endif // ZONECONTAINERWIDGET_H
