#include <QSignalMapper>

#include "network.h"
#include "w_powercontrol.h"

extern NetworkThread *networkThread;

PowerControlWidget::PowerControlWidget(Zone *zone, QWidget *parent) : QWidget(parent)
{
    this->zone = zone;
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    QLabel *stateHeader = new QLabel("State");
    QLabel *toggleNameHeader = new QLabel("Function");
    this->contentLayout->addWidget(toggleNameHeader,0,0);
    this->contentLayout->addWidget(stateHeader,0,1);
    this->contentLayout->addWidget(new QLabel("Action"),0,2);

    connect(networkThread,SIGNAL(powerFunctionsArrived()), this, SLOT(addPowerFunctions()));
    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);
}

void PowerControlWidget::addPowerFunctions()
{
    int x = 1;
    foreach (Zone::PowerFunction pf, zone->powerFunctions)
    {
        QLabel *state = new QLabel("N/A");
        QLabel *toggleName = new QLabel(pf.getName());
        QPushButton *toggle = new QPushButton("Toggle");
        QSignalMapper *signalMapper = new QSignalMapper(this);
        signalMapper->setMapping(toggle,x-1);
        connect(toggle,SIGNAL(clicked()),signalMapper,SLOT(map()));
        connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(togglePower(int)));
        this->contentLayout->addWidget(toggleName,x,0);
        this->contentLayout->addWidget(state,x,1);
        this->contentLayout->addWidget(toggle,x,2);
        zone->powerStatusLabels->insert(x-1, state);
        x++;
    }
    networkThread->GPIOPoll();

}

void PowerControlWidget::togglePower(int id) {
    QJsonObject jsonPayload;
    jsonPayload["type"] = 03;
    jsonPayload["value"] = QString::number(id);
    jsonPayload["zone"] = zone->getId();
    emit(requestingNetworkOut("SET", jsonPayload, ""));
}
