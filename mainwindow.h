#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>

#include "zone.h"
#include "w_zonechooser.h"
#include "w_topheader.h"
#include "w_zonecontainer.h"
#include "network.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    QWidget *topWidget;
    QStackedLayout *contentLayout;
    ZoneContainerWidget *zoneContainer;

private:
    TopHeaderWidget *hcheader;

signals:
    void zoneChanged(Zone zone);
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void showZoneChooser();
    void showSystemLog();
    void showZone(int zone);

private slots:
    void updateEnviroMap(QJsonObject jso, int zone);
};

#endif // MAINWINDOW_H