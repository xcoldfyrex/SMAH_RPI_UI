/*
 Create the first widget you see when opening the application

*/

#include <QFileInfo>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zwavemanager.h"
#include "tcpserver.h"
#include <QDebug>


extern QMap<QString, Zone> gZoneMap;
extern QList<Preset> gColorPresetMap;
extern TCPServer tcpServer;


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("MainWindow");
    this->setStyle(QApplication::style());
    this->setAutoFillBackground(true);
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->resize(1280,800);
    this->update();
    this->repaint();

    this->zoneContainerMap = new QMap<QString, ZoneContainerWidget*>;

    //create header template
    TopHeaderWidget *hcheader = new TopHeaderWidget(this,"Main Menu");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidgetLayout = new QStackedLayout(this);

    this->contentLayout = new QStackedLayout;

    //create node widgets
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);
    SystemSettings *systemSettingsWidget = new SystemSettings(this);
    QWidget *contentHolder = new QWidget(this);
    screensaverHolder = new ScreenSaverWidget(this);
    idleTimer = new QTimer();
    this->idleTimer->start(100*120*5);
    connect(idleTimer,SIGNAL(timeout()), this, SLOT(showSaver()));    
    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(systemSettingsWidget->topWidget);
    setLayout(mainWidgetLayout);
    contentHolder->setLayout(mainLayout);
    mainWidgetLayout->addWidget(contentHolder);
    mainWidgetLayout->addWidget(screensaverHolder->topWidget);
    mainWidgetLayout->setCurrentWidget(screensaverHolder->topWidget);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

    foreach (Zone zone, gZoneMap) {
        ZoneContainerWidget *zcw = new ZoneContainerWidget(zone);
        this->zoneContainerMap->insert(zone.getName(),zcw);
        contentLayout->addWidget(zcw->topWidget);
    }
    contentLayout->setCurrentIndex(0);

    //qRegisterMetaType<smah::Zone>("smah::Zone");

    //connect(networkThread,SIGNAL(zoneDiscovered(smah::Zone)),zoneChooser,SLOT(addZoneButton(smah::Zone)),Qt::QueuedConnection);
    //connect(networkThread,SIGNAL(zoneDiscovered(smah::Zone)),this,SLOT(createZoneElements(smah::Zone)),Qt::QueuedConnection);
    //connect(networkThread,SIGNAL(presetArrived(Preset)),this,SLOT(addPreset(Preset)));
    //connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);

    if (QFileInfo::exists("/dev/ttyACM0"))
    {
        qInfo() << "INIT ZWave";
        init_zwave();
    } else {
        qInfo() << "ZWave device not found. Skipping.";
    }
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

void MainWindow::showZone(QString zone) {
    /* TODO: ADD ERROR HANDLING IF ZONELIST IS NULL */
    //emit zoneChanged(zone);
    contentLayout->setCurrentWidget(this->getZoneContainer(zone)->topWidget);
}

void MainWindow::showSystemWidget() {
    contentLayout->setCurrentIndex(1);
    //contentLayout->setCurrentWidget(this->systemSettingsWidget.topLevelWidget());
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
