#include <QSignalMapper>
#include <QPen>
#include "tcpconnection.h"
#include "light.h"
#include "w_zone_lights.h"
#include "zwavemanager.h"
#include "w_presetchooser.h".h"

ZoneLightsWidget::ZoneLightsWidget(Zone zone, QWidget *parent) : QWidget(parent)
{
    this->zone = zone;
    this->topWidget = new QStackedWidget();
    QWidget *overviewWidget = new QWidget(this);
    this->contentLayout = new QGridLayout(overviewWidget);
    this->topWidget->addWidget(overviewWidget);
    QLabel *toggleNameHeader = new QLabel("Function");
    toggleNameHeader->setObjectName("lblToggleNameHeader");

    this->contentLayout->addWidget(toggleNameHeader,0,0);
    this->contentLayout->addWidget(new QLabel("Action"),0,2);
    this->contentLayout->setAlignment(Qt::AlignTop);

    addToggleFunctions();
}

void ZoneLightsWidget::addToggleFunctions()
{

    int x = 1;
    foreach (Light *light, this->zone.getLightList())
    {
        light->initState();

        QLabel *toggleName = new QLabel(light->getName());
        QSignalMapper *signalMapper = new QSignalMapper(this);
        QPushButton *toggle;
        // Determine what type of light it is
        if (light->getType() == LIGHT_RGB_LED ||
                light->getType() == LIGHT_RGBW_LED ||
                light->getType() ==LIGHT_RGB_INVIDIDUAL_ADDRESS ||
                light->getType() == LIGHT_RGBW_INVIDIDUAL_ADDRESS
                )
        {
            // Can color and shit
            LightControlContainerWidget *colorLightControlWidget = new LightControlContainerWidget(zone, light, this);
            toggle = new QPushButton("Set");
            this->topWidget->addWidget(colorLightControlWidget->topWidget);
            signalMapper->setMapping(toggle,colorLightControlWidget->topWidget);
            connect(toggle,SIGNAL(clicked()),signalMapper,SLOT(map()));
            connect(signalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(showCustomLights(QWidget*)),Qt::QueuedConnection);

            PresetChooser *presetChooserWidget = new PresetChooser(zone, light, this);

            QSignalMapper *presetSignalMapper = new QSignalMapper(this);
            presetSignalMapper->setMapping(colorLightControlWidget->btnShowPreset,presetChooserWidget->topWidget);
            connect(colorLightControlWidget->btnShowPreset,SIGNAL(clicked()),presetSignalMapper,SLOT(map()));
            connect(presetSignalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(showPresetChooser(QWidget*)),Qt::QueuedConnection);
            this->topWidget->addWidget(presetChooserWidget->topWidget);

            //connect(colorLightControlWidget->btnShowPreset,SIGNAL(clicked(bool)),this,SLOT(showPresetChooser()));
        } else {
            // Just on and off
            toggle = new QPushButton("Toggle");
            signalMapper->setMapping(toggle,light->getId());
            connect(toggle,SIGNAL(clicked()),signalMapper,SLOT(map()));
            connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(togglePower(int)));
        }

        this->contentLayout->addWidget(toggleName,x,0);
        this->contentLayout->addWidget(light->statusLabel,x,1);
        this->contentLayout->addWidget(toggle,x,2);
        //zone->powerStatusLabels->insert(x-1, state);
        x++;
    }
    QPushButton *allOn = new QPushButton("All On");
    QPushButton *allOff = new QPushButton("All Off");
    this->contentLayout->addWidget(allOn,0,3);
    this->contentLayout->addWidget(allOff,1,3);

    //networkThread->GPIOPoll();


}

void ZoneLightsWidget::showCustomLights(QWidget *widget)
{
    this->topWidget->setCurrentWidget(widget);
}

void ZoneLightsWidget::togglePower(int id) {
    // TODO
    // why the fuck must i pass an int here instead of the object
    foreach (Light *light, this->zone.getLightList())
    {
        if (light->getId() == id)
            light->toggleState();
    }
}

void ZoneLightsWidget::updateState(Light *light)
{
//light->statusLabel
}

void ZoneLightsWidget::showPresetChooser(QWidget *widget)
{
    this->topWidget->setCurrentWidget(widget);
}
