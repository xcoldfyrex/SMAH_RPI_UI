#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QGridLayout>

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
    QGridLayout *contentLayout;
    QWidget *topWidget;
    MainWindow *myParent;


public slots:
    void addZoneButton(Zone *zone);

private:
};

#endif // MENUWINDOW_H
