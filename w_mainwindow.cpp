/*
 Create the first widget you see when opening the application

*/

#include "w_mainwindow.h"
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
    systemLogWidget = new SystemLogWidget(this);

    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(zoneContainer->topWidget);
    contentLayout->addWidget(systemLogWidget);

    setLayout(mainLayout);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

    connect(networkThread,SIGNAL(zoneArrived(Zone*, int, int)),zoneChooser,SLOT(addZoneButton(Zone*, int, int)),Qt::QueuedConnection);
    connect(networkThread,SIGNAL(presetArrived(Preset*)),zoneContainer->presetChooserWidget,SLOT(addPreset(Preset*)),Qt::QueuedConnection);

    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSend(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(this, SIGNAL(finished()), networkThread, SLOT(deleteLater()));

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
    qDebug() << zone;
    emit zoneChanged(*gZoneMap->value(zone));
    contentLayout->setCurrentIndex(1);
}

void MainWindow::showSystemLog() {
    contentLayout->setCurrentIndex(2);
}

void MainWindow::logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        //systemLogWidget->txtLogger.setText(msg);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
