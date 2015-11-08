#ifndef MAINLIGHTWINDOW_H
#define MAINLIGHTWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include "QPaintEvent"
#include "QPainter"
#include "zone.h"

namespace Ui {
class MainLightWindow;
}

class MainLightWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainLightWindow(QWidget *parent = 0);
    ~MainLightWindow();
    QWidget *topWidget;
    void paintEvent(QPaintEvent *pe);
    QGridLayout *contentLayout;
    Ui::MainLightWindow *ui;



private:
};

#endif // MAINLIGHTWINDOW_H
