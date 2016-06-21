#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "w_mainwindow.h"

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>

#include "w_mainwindow.h"

#include "zone.h"


namespace Ui {
class MenuWindow;
}

class MainWindow;

class ZoneChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneChooserWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    QGridLayout *contentLayout;
    QWidget *topWidget;
    MainWindow *myParent;


public slots:
    void addZoneButton(Zone *zone);

private:
};

#endif // MENUWINDOW_H
