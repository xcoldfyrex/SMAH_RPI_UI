#include "mainwindow.h"
#include "menuwidget.h"
#include "lightcontrolwidget.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("MainWindow");
    this->setStyle(QApplication::style());
    this->setAutoFillBackground(true);
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
    this->repaint();

    //create header template
    HCHeader *hcheader = new HCHeader(this,"Main Menu");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->contentLayout = new QStackedLayout;

    //create node widgets
    MenuWidget *mainMenu = new MenuWidget(this);
    MainLightWindow *mainLightWindow = new MainLightWindow(this);
    LightControlWidget *lightControlWidget = new LightControlWidget(this);

    contentLayout->addWidget(mainMenu->topWidget);
    contentLayout->addWidget(mainLightWindow->topWidget);
    contentLayout->addWidget(lightControlWidget->topWidget);

    setLayout(mainLayout);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addStretch(1);
    mainLayout->addLayout(contentLayout);
    mainLayout->addStretch(1);
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MainWindow::changePage(QWidget *widget)
{
    this->contentLayout->addWidget(widget);

}

void MainWindow::showMenuWindow() {
    contentLayout->setCurrentIndex(0);
}

void MainWindow::showLightWindow() {
    contentLayout->setCurrentIndex(1);
}

void MainWindow::showLightControlWidget() {
    contentLayout->setCurrentIndex(2);
}
