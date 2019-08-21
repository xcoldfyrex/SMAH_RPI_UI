/*
 Create the first widget you see when opening the application

*/

#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zwavemanager.h"
#include "tcpconnectionfactory.h"
#include "widgets/w_zonefunctionsbasewidget.h"
#include <QDebug>

#include <QApplication>
#include <QDir>
#include <QStandardPaths>


extern QList<Preset> gColorPresetMap;
extern TCPConnectionFactory tcpServer;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(1280,800);
    this->move(0,0);
    this->setObjectName("MainWindow");
    this->setStyle(QApplication::style());
    this->setAutoFillBackground(true);
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
    this->repaint();


    //create header template
    TopHeaderWidget *hcheader = new TopHeaderWidget(this,"Main Menu");
    hcheader->setObjectName("TopHeaderWidget");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    ZoneFunctionsBaseWidget *zoneBase = new ZoneFunctionsBaseWidget(this);
    zoneBase->setObjectName("ZoneFunctionsBaseWidget");

    mainWidgetLayout = new QStackedLayout(this);

    this->contentLayout = new QStackedLayout;

    //create node widgets
    SystemSettings *systemSettingsWidget = new SystemSettings(this);
    QWidget *contentHolder = new QWidget(this);
    screensaverHolder = new ScreenSaverWidget(this);

    idleTimer = new QTimer();
    this->idleTimer->start(100*120*5);
    connect(idleTimer,SIGNAL(timeout()), this, SLOT(showSaver()));
    contentLayout->addWidget(zoneBase->topWidget);
    contentLayout->addWidget(systemSettingsWidget->topWidget);
    setLayout(mainWidgetLayout);
    contentHolder->setLayout(mainLayout);
    mainWidgetLayout->addWidget(contentHolder);
    mainWidgetLayout->addWidget(screensaverHolder->topWidget);
    mainWidgetLayout->setCurrentWidget(screensaverHolder->topWidget);

    mainLayout->setContentsMargins(0,0,0,0);
    mainWidgetLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

    contentLayout->setCurrentIndex(0);
    contentLayout->setContentsMargins(0,0,0,0);

    if (QFileInfo::exists("/dev/ttyACM0"))
    {
        qInfo() << "INIT ZWave";
        init_zwave();
    } else {
        qInfo() << "ZWave device not found. Skipping.";
    }

}

void MainWindow::paintEvent(QPaintEvent *)
{

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MainWindow::showZoneChooser() {
    contentLayout->setCurrentIndex(0);
}

void MainWindow::showSystemWidget() {
    contentLayout->setCurrentIndex(1);
}

void MainWindow::addPreset(Preset preset)
{
    if (gColorPresetMap.size() > 0)
    {
        foreach (Preset old_preset, gColorPresetMap)
        {
            if (old_preset.id == preset.id)
                return;
        }
    }
    gColorPresetMap.append(preset);
}

void MainWindow::hideSaver()
{
    this->mainWidgetLayout->setCurrentIndex(0);
}

void MainWindow::showSaver()
{
    this->mainWidgetLayout->setCurrentIndex(1);
}

void MainWindow::resetIdle(QEvent *ev)
{
    if (this->mainWidgetLayout->currentIndex() != 0)
    {
        ev->ignore();
        ev->setAccepted(false);
        hideSaver();
    }
    this->idleTimer->stop();
    this->idleTimer->start(100*60*5);
}
