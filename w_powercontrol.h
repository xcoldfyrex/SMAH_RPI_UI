#ifndef POWERCONTROLWIDGET_H
#define POWERCONTROLWIDGET_H

#include "zone.h"

class Zone;

class PowerControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerControlWidget(Zone *zone, QWidget *parent = 0);
    QWidget *topWidget;

private:
    Zone *zone;
    QGridLayout *contentLayout;

signals:

public slots:
};

#endif // POWERCONTROLWIDGET_H
