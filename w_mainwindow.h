#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "w_topheader.h"
#include "w_zonecontainer.h"
#include "w_systemlog.h"
#include "zone.h"
#include "network.h"

#include <QWidget>
#include <QPaintEvent>
#include <QStackedLayout>
#include <QStyleOption>

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
    NetworkThread *networkConnection;
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
};

#endif // MAINWINDOW_H
