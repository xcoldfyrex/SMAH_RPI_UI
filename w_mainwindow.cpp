/*
 Create the first widget you see when opening the application

*/

#include "w_mainwindow.h"
#include "w_zonechooser.h"
#include "w_lightcontrolcontainer.h"
#include "ui_mainwindow.h"
#include "network.h"

#include <QDebug>
#include <QSignalMapper>

extern Zone *gActiveZone;
extern QList<Zone*> *gZoneList;
extern NetworkThread *networkConnection;

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
    TopHeaderWidget *hcheader = new TopHeaderWidget(this,"Main Menu");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    this->contentLayout = new QStackedLayout;

    //create node widgets
    zoneContainer = new ZoneContainerWidget(this);
    ZoneChooserWidget *zoneChooser = new ZoneChooserWidget(this);
    systemLogWidget = new SystemLogWidget(this);

    contentLayout->addWidget(zoneChooser->topWidget);
    contentLayout->addWidget(zoneContainer->topWidget);
    contentLayout->addWidget(systemLogWidget);

    setLayout(mainLayout);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(hcheader->topWidget);
    mainLayout->addLayout(contentLayout);

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
    zone--;
    emit zoneChanged(*gZoneList->at(zone));
    contentLayout->setCurrentIndex(1);
}

void MainWindow::showSystemLog() {
    contentLayout->setCurrentIndex(2);
}

void MainWindow::startNetworking()
{
    //setup networking
    NetworkThread *thread = new NetworkThread("127.0.0.1", 9002, this);
    networkConnection = thread;

    //networkConnection->run();
    networkConnection->start();
    connect(this, SIGNAL(finished()), networkConnection, SLOT(deleteLater()));
}

void MainWindow::logHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        //systemLogWidget->txtLogger.setText(msg);
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

void MainWindow::sendToNetwork(QString command, QJsonObject jsonPayload) {
    jsonPayload["zone"] = gActiveZone->id;
    networkConnection->prepareToSend(command,jsonPayload, "");
}
