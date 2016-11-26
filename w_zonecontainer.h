#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>

#include "w_zoneoverview.h"
#include "w_presetchooser.h"
#include "w_zonecontainerheader.h"

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


private:

private slots:
    void showLightContainer();
    void showOverview();
    void showPresetChooser();
    void showActions();

};

#endif // ZONECONTAINERWIDGET_H
