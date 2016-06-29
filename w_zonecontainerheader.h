#ifndef ZONECONTAINERHEADERWIDGET_H
#define ZONECONTAINERHEADERWIDGET_H


#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "zone.h"

class ZoneContainerHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ZoneContainerHeaderWidget(QWidget *parent = 0);
    QWidget *topWidget;
    void setActiveZone(Zone zone);
    QLabel *lblZoneName;

private:
    QLabel *lblClock;
    QSpacerItem *spcHeader;
    QHBoxLayout *topWidgetLayout;
    QLabel *lblZoneLightPreset;
signals:

public slots:
    void switchZone(Zone zone);
    void changePreset(QString preset);
};

#endif // ZONECONTAINERHEADERWIDGET_H
