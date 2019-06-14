#include "ui_mainwindow.h"
#include "ui_ui_mainwindow.h"

UI_MainWindow::UI_MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ui_mainwindow)
{
    ui->setupUi(this);
}

UI_MainWindow::~UI_MainWindow()
{
    delete ui;
}
