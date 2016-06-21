#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPaintEvent>
#include <QStackedLayout>
#include <QStyleOption>

#include "zone.h"
#include "w_zonechooser.h"
#include "w_topheader.h"
#include "w_zonecontainer.h"
#include "w_systemlog.h"
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
    SystemLogWidget *systemLogWidget;
    static void logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    TopHeaderWidget *hcheader;

signals:
    void zoneChanged(Zone zone);

public slots:
    void showZoneChooser();
    void showSystemLog();
    void showZone(int zone);
    void startNetworking();
    void sendToNetwork(QString command, QJsonObject jsonPayload);
};

#endif // MAINWINDOW_H
