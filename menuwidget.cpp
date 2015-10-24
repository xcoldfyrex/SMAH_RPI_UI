#include "menuwidget.h"
#include "mainwindow.h"
#include "ui_menuwindow.h"
#include <QDebug>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->btnMainEnvrionment,0,0);
    contentLayout->addWidget(ui->btnMainPower,0,1);
    contentLayout->addWidget(ui->btnMainLight,0,2);
    contentLayout->addWidget(ui->btnMainHealth,0,3);
    contentLayout->addWidget(ui->btnMainInfo,1,0);

    MainWindow* myParent = dynamic_cast<MainWindow*>(parent);
    connect(ui->btnMainLight,SIGNAL(clicked(bool)),myParent,SLOT(showLightWindow()));


}

MenuWidget::~MenuWidget()
{
    delete ui;
}



void MenuWidget::paintEvent(QPaintEvent *pe) {
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}
