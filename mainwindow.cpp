/*
 Create the first widget you see when opening the application

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpconnectionfactory.h"

#include <QDebug>

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QQuickView>

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QWindow>

extern QMap<int, Preset*> gColorPresetMap;
extern TCPConnectionFactory tcpServer;
extern QMap<QString, Zone*> gZoneMap;

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{   
    this->setFixedSize(1280,800);
    this->move(0,0);
    this->setObjectName("MainWindow");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    this->contentLayout = new QStackedLayout;

    idleTimer = new QTimer();
    this->idleTimer->start(100*120*5);
    connect(idleTimer,SIGNAL(timeout()), this, SLOT(showSaver()));

    setLayout(mainLayout);

    // setup QML bits

    QVariantList qmlZones;
    QVariantList qmlPresets;
    //QVariantMap qmlLights;


    foreach (QString key, gZoneMap.keys())
    {
        qmlZones.append(QVariant::fromValue(gZoneMap.value(key)));
    }

    foreach (Preset *preset, gColorPresetMap)
    {
        qmlPresets.append(QVariant::fromValue(preset));
    }

    //foreach (Light *light, g_lightMap)
    //{
//        qmlLights.insert(light->getName(), QVariant::fromValue(light));
  //  }

    qmlRegisterType<Light>("smah.light", 1, 0, "Light");
    qmlRegisterType<Zone>("smah.zone", 1, 0, "Zone");
    qmlRegisterType<Zone>("smah.preset", 1, 0, "Preset");

    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);

    engine->rootContext()->setContextProperty("zoneList", QVariant::fromValue(qmlZones));
    engine->rootContext()->setContextProperty("applicationDirPath", QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory));

    QQuickView *qmlView = new QQuickView(engine, qobject_cast<QWindow*>(this));
    qmlView->setSource(QUrl(QStringLiteral("qrc:/Main.qml")));

    QWidget *container = QWidget::createWindowContainer(qmlView);

    container->resize(this->width(),500);
    mainLayout->addWidget(container);
    mainLayout->setContentsMargins(0,0,0,0);


}

void MainWindow::paintEvent(QPaintEvent *)
{

    //QStyleOption o;
    //o.initFrom(this);
    //QPainter p(this);
    //style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}


void MainWindow::hideSaver()
{
    // this->mainWidgetLayout->setCurrentIndex(0);
}

void MainWindow::showSaver()
{
    //this->mainWidgetLayout->setCurrentIndex(1);
}

void MainWindow::resetIdle(QEvent *ev)
{
    return;
    if (this->mainWidgetLayout->currentIndex() != 0)
    {
        ev->ignore();
        ev->setAccepted(false);
        hideSaver();
    }
    this->idleTimer->stop();
    this->idleTimer->start(100*60*5);
}
