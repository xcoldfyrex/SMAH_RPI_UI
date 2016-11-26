#include "w_scheduledactions.h"

ScheduledActionsWidget::ScheduledActionsWidget(QWidget *parent) : QWidget(parent)
{

    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->actiontList = new QListWidget(this);

    contentLayout->addWidget(actiontList);

    actiontList->setObjectName("actiontList");

}
