#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>

#include "w_zonechooser.h"
#include "w_topheader.h"
#include "network.h"
#include "zone.h"


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

signals:
    void zoneChanged(Zone *zone);
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void showZoneChooser();
    void showSystemLog();
    void showZone(int zone);
    void addPreset(Preset *preset);


private slots:
    void addZoneLayout(Zone *zone);
};

#endif // MAINWINDOW_H
