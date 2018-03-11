/*
 Create the first widget you see when opening the application

*/

#include "mainwindow.h"
#include "w_lightcontrolcontainer.h"
#include "ui_mainwindow.h"
#include "network.h"

extern QMap<int, Zone*> *gZoneMap;
extern NetworkThread *networkThread;
extern QList<Preset> gPresetList;

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
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);
    SystemSettings *systemSettingsWidget = new SystemSettings(this);

    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(systemSettingsWidget->topWidget);
    setLayout(mainLayout);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

    connect(networkThread,SIGNAL(zoneDiscovered(Zone*, int, int)),zoneChooser,SLOT(addZoneButton(Zone*, int, int)),Qt::QueuedConnection);
    connect(networkThread,SIGNAL(zoneDiscovered(Zone*, int, int)),this,SLOT(addZoneLayout(Zone*)),Qt::QueuedConnection);
    connect(networkThread,SIGNAL(presetArrived(Preset)),this,SLOT(addPreset(Preset)));
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
    emit zoneChanged(gZoneMap->value(zone));
    contentLayout->setCurrentWidget(gZoneMap->value(zone)->zoneFunctionContainer->topWidget);
}

void MainWindow::showSystemWidget() {
    contentLayout->setCurrentIndex(1);
    //contentLayout->setCurrentWidget(this->systemSettingsWidget.topLevelWidget());
}

void MainWindow::addZoneLayout(Zone *zone)
{
    contentLayout->addWidget(zone->zoneFunctionContainer->topWidget);
}

void MainWindow::addPreset(Preset preset)
{
    if (gPresetList.size() > 0)
    {
        foreach (Preset old_preset, gPresetList)
        {
            if (old_preset.id == preset.id)
                return;
        }
    }
    gPresetList.append(preset);
}
