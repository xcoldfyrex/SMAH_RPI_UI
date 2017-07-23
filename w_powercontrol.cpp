#include "w_powercontrol.h"

PowerControlWidget::PowerControlWidget(Zone *zone, QWidget *parent) : QWidget(parent)
{
    this->zone = zone;
    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
}
