#ifndef ZONEENVIRONMENT_H
#define ZONEENVIRONMENT_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "zone.h"

class ZoneEnvironmentPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneEnvironmentPanel(QWidget *parent = 0);
    ZoneEnvironmentPanel(QWidget *parent, Zone *zone);
    QWidget *topWidget;

private:
    QGridLayout *contentLayout;
    QLabel *lblZoneEnvHeader;
    QLabel *lblZoneEnvData;

signals:

public slots:
};

#endif // ZONEENVIRONMENT_H
