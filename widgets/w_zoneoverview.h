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
    explicit ZoneOverviewWidget(Zone zone, QWidget *parent = 0);
    QWidget *topWidget;
    QGridLayout *contentLayout;

private:
    float rawVoltage(int reading);
    QTimer *updateTimer;
    Zone zone;
    QLabel *lblReadingsDisplay;

signals:

private slots:
    void updateReadings();
};

#endif // ZONEOVERVIEWWIDGET_H
