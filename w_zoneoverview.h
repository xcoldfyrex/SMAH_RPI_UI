#ifndef ZONEOVERVIEWWIDGET_H
#define ZONEOVERVIEWWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class ZoneOverviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneOverviewWidget(QWidget *parent = 0);
    QWidget *topWidget;
    QGridLayout *contentLayout;
    QLabel *lblZoneName;
    QLabel *lblZoneTemp;
    QLabel *lblZoneRH;
    QLabel *lblZoneLightPreset;

signals:

public slots:
};

#endif // ZONEOVERVIEWWIDGET_H
