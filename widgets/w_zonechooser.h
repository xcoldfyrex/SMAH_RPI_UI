#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMap>
#include <QListWidget>

#include "mainwindow.h"
#include "zone2.h"

namespace Ui {
class MenuWindow;
}

class MainWindow;

class ZoneChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneChooserWidget(QWidget *parent = 0);
    QHBoxLayout *contentLayout;
    QWidget *topWidget;
    MainWindow *myParent;

public slots:
    void getZoneFromSelected();

private:
    QMap<Zone,QPushButton> zoneSelectorMap;
    int offset = 0;
    QListWidget *zoneList;

};

#endif // MENUWINDOW_H
