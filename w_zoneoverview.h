#ifndef ZONEOVERVIEWWIDGET_H
#define ZONEOVERVIEWWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "zone.h"

class ZoneOverviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneOverviewWidget(QWidget *parent = 0);
    QWidget *topWidget;
    QGridLayout *contentLayout;
    QLabel *lblZoneTemp;
    QLabel *lblZoneRH;

signals:

public slots:
    void changeTemperature(QString temp);
    void changeRH(QString rh);
};

#endif // ZONEOVERVIEWWIDGET_H
