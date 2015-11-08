#include "mainlightwindow.h"
#include "ui_mainlightwindow.h"
#include "mainwindow.h"
#include <QDebug>
#include <QPushButton>

extern QList<Zone> *zoneList;

MainLightWindow::MainLightWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainLightWindow)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->label,0,0);

    int gridLoc = 1;
    foreach (Zone zone, *zoneList) {
        QPushButton *zonelabel = new QPushButton(zone.name);
        MainWindow* myParent = dynamic_cast<MainWindow*>(parent);
        connect(zonelabel,SIGNAL(clicked(bool)),myParent,SLOT(showLightControlWidget()));

        contentLayout->addWidget(zonelabel,gridLoc,0);
        qDebug() << "ZONE " << zone.name;
        gridLoc++;
    }
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
