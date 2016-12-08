#include "w_systemlog.h"
#include "ui_w_systemlog.h"

SystemLogWidget::SystemLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemLogWidget)
{
    ui->setupUi(this);
    //this->txtLogger = ui->txtLog;
    this->ui->txtLog->viewport()->setAutoFillBackground(false);

}

SystemLogWidget::~SystemLogWidget()
{
    delete ui;
}
