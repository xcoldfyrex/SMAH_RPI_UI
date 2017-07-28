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
}

void PowerControlWidget::addPowerFunctions()
{
    int x = 1;
    foreach (Zone::PowerFunction pf, zone->powerFunctions)
    {
        QLabel *state = new QLabel("N/A");
        QLabel *toggleName = new QLabel(pf.name);
        QPushButton *toggle = new QPushButton("Toggle");
        toggle->setShortcut(0);
        this->contentLayout->addWidget(toggleName,x,0);
        this->contentLayout->addWidget(state,x,1);
        this->contentLayout->addWidget(toggle,x,2);
        zone->powerStatusLabels->insert(x-1, state);
        x++;
    }
    networkThread->GPIOPoll();

}
