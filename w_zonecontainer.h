#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include "w_zoneoverview.h"

#include <QWidget>
#include <QStackedLayout>

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(QWidget *parent = 0);
    ZoneOverviewWidget *zoneOverViewWidget;
    QWidget *topWidget;
    QStackedLayout *contentLayout;


private:

private slots:
    void showLightContainer();
    void showOverview();
    void showPresetChooser();

};

#endif // ZONECONTAINERWIDGET_H
