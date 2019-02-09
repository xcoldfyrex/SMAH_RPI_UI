#ifndef ZONEENVIRONMENT_H
#define ZONEENVIRONMENT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QMap>
#include <QList>

#include "zone.h"

class ZoneEnvironmentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneEnvironmentPanel(QWidget *parent = nullptr);
    ZoneEnvironmentPanel(QWidget *parent, Zone zone);
    QWidget *topWidget;

private:
    QGridLayout *contentLayout;
    QLabel *lblZoneEnvHeader;
    QLabel *lblZoneEnvData;
    QTimer *updateTimer;
    Zone zone;
    float rawVoltage(int reading);

signals:

public slots:

private slots:
    void enviroUpdate();

};

#endif // ZONEENVIRONMENT_H
