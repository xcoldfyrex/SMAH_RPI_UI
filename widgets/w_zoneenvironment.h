#ifndef ZONEENVIRONMENT_H
#define ZONEENVIRONMENT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QMap>
#include <QList>

#include "zone.h"
#include "qengravedlabel.h"

class ZoneEnvironmentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneEnvironmentPanel(QWidget *parent = nullptr);
    ZoneEnvironmentPanel(QWidget *parent, Sensor *sensor, bool compact = false);
    QWidget *topWidget;

private:
    QGridLayout *contentLayout;
    QEngravedLabel *lblZoneEnvHeader;
    QEngravedLabel *lblZoneEnvData;
    QTimer *updateTimer;
    Sensor *sensor;
    float rawVoltage(int reading);

signals:

public slots:

private slots:
    void enviroUpdate();

};

#endif // ZONEENVIRONMENT_H
