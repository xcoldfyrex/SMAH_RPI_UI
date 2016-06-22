#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include <QWidget>
#include <QStackedWidget>

#include "w_zoneoverview.h"
#include "w_presetchooser.h"

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(QWidget *parent = 0);
    ZoneOverviewWidget *zoneOverViewWidget;
    QWidget *topWidget;
    QStackedWidget *contentLayout;
    PresetChooser *presetChooserWidget = new PresetChooser(this);

private:

private slots:
    void showLightContainer();
    void showOverview();
    void showPresetChooser();

};

#endif // ZONECONTAINERWIDGET_H
