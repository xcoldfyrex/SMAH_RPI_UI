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
    void setActiveZone(Zone zone);
    QWidget *topWidget;
    QGridLayout *contentLayout;
    QLabel *lblZoneName;
    QLabel *lblZoneTemp;
    QLabel *lblZoneRH;
    QLabel *lblZoneLightPreset;

signals:

public slots:
    void switchZone(Zone zone);
    void changePreset(QString preset);
    void changeTemperature(QString temp);
    void changeRH(QString rh);
};

#endif // ZONEOVERVIEWWIDGET_H
