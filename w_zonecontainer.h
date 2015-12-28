#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#include "w_zoneoverview.h"

#include <QWidget>

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(QWidget *parent = 0);
    ZoneOverviewWidget *zoneOverViewWidget;
    QWidget *topWidget;

private:
};

#endif // ZONECONTAINERWIDGET_H
