#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "hcheader.h"
#include "mainlightwindow.h"
#include <QPaintEvent>
#include "QPainter"
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
    void changePage(QWidget *widget);
    MainLightWindow *mainLightWindow;


private:
    HCHeader *hcheader;


signals:


public slots:
    void showMenuWindow();
    void showLightWindow();
    void showLightControlWidget();
};

#endif // MAINWINDOW_H
