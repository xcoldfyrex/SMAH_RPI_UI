#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMap>
#include <QListWidget>

#include "w_zonefunctionsbasewidget.h"
#include "zone.h"
#include "qengravedlabel.h"

namespace Ui {
class MenuWindow;
}

class MainWindow;

class ZoneChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneChooserWidget(QWidget *parent = nullptr);
    QVBoxLayout *contentLayout;
    QWidget *topWidget;
    ZoneFunctionsBaseWidget *myParent;

public slots:
    void getZoneFromSelected();

private:
    QMap<Zone,QPushButton> zoneSelectorMap;
    QEngravedList *zoneList;
    int offset = 0;

};

#endif // MENUWINDOW_H
