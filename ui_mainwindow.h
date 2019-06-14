#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QWidget>

namespace Ui {
class ui_mainwindow;
}

class UI_MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UI_MainWindow(QWidget *parent = nullptr);
    ~UI_MainWindow();

private:
    Ui::ui_mainwindow *ui;
};

#endif // UI_MAINWINDOW_H
