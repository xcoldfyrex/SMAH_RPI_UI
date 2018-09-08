#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QMap>
#include <QPainter>

#include "zone.h"
#include "tcpconnection.h"

#include "widgets/w_zonechooser.h"
#include "widgets/w_topheader.h"
#include "widgets/w_systemsettings.h"
#include "widgets/w_zonecontainer.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    QWidget *topWidget;
    QStackedLayout *contentLayout;

private:
    TopHeaderWidget *hcheader;
    QMap<QString, ZoneContainerWidget*> *zoneContainerMap;
    ZoneContainerWidget *getZoneContainer(QString zone) { return zoneContainerMap->value(zone); }


signals:
    void zoneChanged(Zone);
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void showZoneChooser();
    void showSystemWidget();
    void showZone(QString zone);
    void addPreset(Preset preset);


private slots:
    void createZoneElements(Zone zone);
};

#endif // MAINWINDOW_H
