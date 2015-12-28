#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "w_topheader.h"
#include "w_zonecontainer.h"
#include "zone.h"

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

private:
    TopHeaderWidget *hcheader;

signals:
    void zoneChanged(Zone zone);

public slots:
    void showZoneChooser();
    void showZone(int zone);
};

#endif // MAINWINDOW_H
