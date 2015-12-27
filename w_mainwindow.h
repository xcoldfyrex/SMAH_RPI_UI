#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "w_topheader.h"
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

private:
    TopHeaderWidget *hcheader;

signals:


public slots:
    void showMenuWindow();
    void showZone(QString zone);
};

#endif // MAINWINDOW_H
