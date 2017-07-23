#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

#include "w_zoneoverview.h"
#include "w_presetchooser.h"
#include "w_zonecontainerheader.h"
#include "zone.h"

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(QWidget *parent = 0);
    ZoneOverviewWidget *zoneOverViewWidget;
    QWidget *topWidget;
    QStackedWidget *contentLayout;
    PresetChooser *presetChooserWidget = new PresetChooser(this);
    ZoneContainerHeaderWidget *zoneContainerHeader;
    QPushButton *btnShowLights = new QPushButton;
    QPushButton *btnShowPower = new QPushButton;
    QPushButton *btnShowActions = new QPushButton;


private:

private slots:
    void showLightContainer();
    void showOverview();
    void showPresetChooser();
    void showActions();

};

#endif // ZONECONTAINERWIDGET_H
