#ifndef ZONECONTAINERHEADERWIDGET_H
#define ZONECONTAINERHEADERWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "zone.h"

class Zone;

class ZoneContainerHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneContainerHeaderWidget(Zone *zone, QWidget *parent = 0);
    QWidget *topWidget;

private:
    QLabel *lblClock;
    QSpacerItem *spcHeader;
    QHBoxLayout *topWidgetLayout;
    QLabel *lblZoneLightPreset;
    QLabel *lblZoneName;

signals:

public slots:
    void changePreset(QString preset);
};

#endif // ZONECONTAINERHEADERWIDGET_H
