/*
 Create the first widget you see when opening the application

*/

#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zwavemanager.h"
#include "tcpconnectionfactory.h"
#include "w_weatherwidget.h"

#include <QDebug>

#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QQuickView>

#include <QQuickWidget>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QWindow>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQmlPropertyMap>

extern QList<Preset> gColorPresetMap;
extern TCPConnectionFactory tcpServer;
extern QMap<QString, Zone*> gZoneMap;
extern QMap<int, Light*> g_lightMap;

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
    QVariantMap qmlLights;

    foreach (QString key, gZoneMap.keys())
    {
        qmlZones.append(QVariant::fromValue(gZoneMap.value(key)));
        qDebug() << gZoneMap.value(key)->getLightList().size();
    }
    foreach (Light *light, g_lightMap)
    {
        qmlLights.insert(light->getName(), QVariant::fromValue(light));
    }

    qmlRegisterType<Light>("smah.light", 1, 0, "Light");
    qmlRegisterType<Zone>("smah.zone", 1, 0, "Zone");
    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);

    engine->rootContext()->setContextProperty("zoneList", QVariant::fromValue(qmlZones));
    engine->rootContext()->setContextProperty("lightList", qmlLights);
    engine->load(QUrl(QStringLiteral("qrc:/Main.qml")));


    QQuickView *qmlView = new QQuickView(engine, qobject_cast<QWindow*>(this));
    qmlView->setSource(QUrl(QStringLiteral("qrc:/Main.qml")));
    QWidget *container = QWidget::createWindowContainer(qmlView);



    //auto object = new QQmlPropertyMap(container);
    //object->insert("name", QVariant::fromValue(QString("")));

    /*
    QObject *oRootObject = dynamic_cast<QObject*>(engine->rootObjects().first());
    QObject *oBottomBlock = oRootObject->findChild<QObject*>("mainMenu");

    if (oBottomBlock) {

        QQmlComponent oComponent(engine,QUrl(QString("qrc:/LightControls.qml")));
        QQuickItem *oItemButtonExit = qobject_cast<QQuickItem*>(oComponent.create());
        oItemButtonExit->setParentItem(qobject_cast<QQuickItem*>(oBottomBlock));
        oItemButtonExit->setParent(qobject_cast<QQuickItem*>(oBottomBlock));

    }
    */

    container->resize(this->width(),500);
    //zoneBase->topWidget->setFixedSize(this->width(),400);
    mainLayout->addWidget(container);
    //mainLayout->addWidget(zoneBase->topWidget);

    mainLayout->setContentsMargins(0,0,0,0);



    //mainWidgetLayout->addWidget(container);

    //contentHolder->setLayout(mainLayout);
    //mainWidgetLayout->addWidget(contentHolder);
    //mainWidgetLayout->addWidget(screensaverHolder->topWidget);
    //mainWidgetLayout->setCurrentWidget(screensaverHolder->topWidget);

    //mainLayout->setContentsMargins(0,0,0,0);
    //mainWidgetLayout->setContentsMargins(0,0,0,0);
    //mainLayout->addWidget(hcheader->topWidget);
    //mainWidgetLayout->addWidget(container);
    //mainLayout->addLayout(contentLayout);

    //contentLayout->setCurrentIndex(2);
    //contentLayout->setContentsMargins(0,0,0,0);

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

    //QStyleOption o;
    //o.initFrom(this);
    //QPainter p(this);
    //style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MainWindow::showZoneChooser() {
    contentLayout->setCurrentIndex(0);
}

void MainWindow::showSystemWidget() {
    contentLayout->setCurrentIndex(1);
}

void MainWindow::showWeatherWidget() {
    contentLayout->setCurrentIndex(2);
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
