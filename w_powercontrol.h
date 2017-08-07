#ifndef POWERCONTROLWIDGET_H
#define POWERCONTROLWIDGET_H

#include <QTableWidgetItem>
#include <QTableWidget>

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
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:

private slots:
    void addPowerFunctions();
    void togglePower(int id);
};

#endif // POWERCONTROLWIDGET_H
