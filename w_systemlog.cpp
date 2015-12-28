#include "w_systemlog.h"
#include "ui_w_systemlog.h"

SystemLogWidget::SystemLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemLogWidget)
{
    ui->setupUi(this);
}

SystemLogWidget::~SystemLogWidget()
{
    delete ui;
}
