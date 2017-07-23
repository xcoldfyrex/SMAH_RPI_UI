/*
 Create the first widget you see when opening the application

*/

#include "mainwindow.h"
#include "w_lightcontrolcontainer.h"
#include "ui_mainwindow.h"
#include "network.h"

#include <QSignalMapper>

extern Zone *gActiveZone;
extern QMap<int, Zone*> *gZoneMap;
extern NetworkThread *networkThread;

Q_DECLARE_METATYPE(Zone)

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{

    //setup networking
    networkThread = new NetworkThread("10.1.10.110", 9002, this);

    this->setObjectName("MainWindow");
    this->setStyle(QApplication::style());
    this->setAutoFillBackground(true);
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->resize(800,480);
    this->update();
    this->repaint();

    //create header template
    TopHeaderWidget *hcheader = new TopHeaderWidget(this,"Main Menu");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->contentLayout = new QStackedLayout;

    //create node widgets
    this->zoneContainer = new ZoneContainerWidget(this);
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);

    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(zoneContainer->topWidget);

    setLayout(mainLayout);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

    connect(networkThread,SIGNAL(zoneDiscovered(Zone*, int, int)),zoneChooser,SLOT(addZoneButton(Zone*, int, int)),Qt::QueuedConnection);
    connect(networkThread,SIGNAL(presetArrived(Preset*)),zoneContainer->presetChooserWidget,SLOT(addPreset(Preset*)),Qt::QueuedConnection);
    connect(networkThread,SIGNAL(zoneResourceArrived(QJsonObject, int)),this,SLOT(updateEnviroMap(QJsonObject, int)),Qt::QueuedConnection);
    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &p, this);
}

void MainWindow::showZoneChooser() {
    contentLayout->setCurrentIndex(0);
}

void MainWindow::showZone(int zone) {
    /* TODO: ADD ERROR HANDLING IF ZONELIST IS NULL */
    Zone newzone = *gZoneMap->value(zone);
    emit zoneChanged(newzone);
    contentLayout->setCurrentIndex(1);
    zoneContainer->btnShowPower->setEnabled(newzone.hasPower);
    qDebug() << newzone.hasLedRGB;
    qDebug() << newzone.hasLedWhite;
    if (newzone.hasLedRGB || newzone.hasLedWhite)
    {
        this->zoneContainer->btnShowLights->setEnabled(false);
    } else {
        this->zoneContainer->btnShowLights->setEnabled(false);
    }
}

void MainWindow::showSystemLog() {
    contentLayout->setCurrentIndex(2);
}

void MainWindow::updateEnviroMap(QJsonObject jso, int zone)
{
    QList<int> values;
    foreach (const QJsonValue &jsonvalue, jso) {
        int value = jsonvalue.toInt();
        values.append(value);
    }
    gZoneMap->value(zone)->environmentMap.insert(zone, values);
}
