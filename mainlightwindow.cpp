#include "mainlightwindow.h"
#include "ui_mainlightwindow.h"

MainLightWindow::MainLightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainLightWindow)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->label,0,0);
}

MainLightWindow::~MainLightWindow()
{
    delete ui;
}

void MainLightWindow::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
