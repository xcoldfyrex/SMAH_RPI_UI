#ifndef ZONEOVERVIEWWIDGET_H
#define ZONEOVERVIEWWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTimer>

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

private:
    float rawVoltage(int reading);
    QTimer *updateTimer;

signals:

private slots:
    void updateReadings();
};

#endif // ZONEOVERVIEWWIDGET_H
