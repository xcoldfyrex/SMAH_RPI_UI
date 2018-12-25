#include <QSignalMapper>
#include <QPen>
#include "light.h"
#include "w_zone_lights.h"
#include "zwavemanager.h"
#include "w_presetchooser.h"

#include <QDebug>

extern QMap <int, Light*> g_lightMap;

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
        //light->initState();

        QLabel *toggleName = new QLabel(light->getName());
        toggleName->setObjectName("lblToggleName");
        QSignalMapper *signalMapper = new QSignalMapper(this);
        QPushButton *toggle;
        QSlider *slider;
        // Determine what type of light it is
        if (light->getType() == LIGHT_RGB_LED ||
                light->getType() == LIGHT_RGBW_LED ||
                light->getType() ==LIGHT_RGB_INVIDIDUAL_ADDRESS ||
                light->getType() == LIGHT_RGBW_INVIDIDUAL_ADDRESS
                )
        {
            // Can color and shit
            LightControlContainerWidget *colorLightControlWidget = new LightControlContainerWidget(zone, light, this);
            toggle = new QPushButton("> Set");
            toggle->setObjectName("btnShowLightControl");
            this->topWidget->addWidget(colorLightControlWidget->topWidget);
            signalMapper->setMapping(toggle,colorLightControlWidget->topWidget);
            connect(toggle,SIGNAL(clicked()),signalMapper,SLOT(map()));
            connect(signalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(showCustomLights(QWidget*)),Qt::QueuedConnection);

            PresetChooser *presetChooserWidget = new PresetChooser(zone, light, this);
            light->lcwWidget = colorLightControlWidget;

            QSignalMapper *presetSignalMapper = new QSignalMapper(this);
            presetSignalMapper->setMapping(colorLightControlWidget->btnSetPreset,presetChooserWidget->topWidget);
            connect(colorLightControlWidget->btnSetPreset,SIGNAL(clicked(bool)),presetSignalMapper,SLOT(map()));
            connect(presetSignalMapper,SIGNAL(mapped(QWidget*)),this,SLOT(showPresetChooser(QWidget*)),Qt::QueuedConnection);
            this->topWidget->addWidget(presetChooserWidget->topWidget);

            connect(presetChooserWidget->btnBack,SIGNAL(clicked(bool)),this, SLOT(hidePresetChooser()));
            connect(colorLightControlWidget->btnBack,SIGNAL(clicked(bool)),this, SLOT(hidePresetChooser()));


            this->topWidget->addWidget(presetChooserWidget->topWidget);
            this->contentLayout->addWidget(toggle,x,2);
        } else if (light->getType() == 1) {
            slider = new QSlider(Qt::Horizontal);
            slider->setMaximum(100);
            slider->setMinimum(1);
            this->contentLayout->addWidget(slider,x,2);
            slider->setMaximumWidth(800);
        } else {
            // Just on and off
            toggle = new QPushButton("> Toggle");
            toggle->setObjectName("btnShowLightControl");
            signalMapper->setMapping(toggle,light->getId());
            connect(toggle,SIGNAL(clicked()),signalMapper,SLOT(map()));
            connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(togglePower(int)));
            this->contentLayout->addWidget(toggle,x,2);

        }

        this->contentLayout->addWidget(toggleName,x,0);
        this->contentLayout->addWidget(light->statusLabel,x,1);
        //zone->powerStatusLabels->insert(x-1, state);
        x++;
    }
    QPushButton *allOn = new QPushButton("All On");
    QPushButton *allOff = new QPushButton("All Off");
    this->contentLayout->addWidget(allOn,x+2,0);
    this->contentLayout->addWidget(allOff,x+2,1);
}

void ZoneLightsWidget::showCustomLights(QWidget *widget)
{
    this->zone.pageStack.append(widget);
    // THIS NEEDS TO GO TO THE ZONE FUNCTIONS STACK
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

}

void ZoneLightsWidget::showPresetChooser(QWidget *widget)
{
    this->topWidget->setCurrentWidget(widget);
}

void ZoneLightsWidget::hidePresetChooser()
{
    this->topWidget->setCurrentIndex(0);
}


void ZoneLightsWidget::buttonListClicked(int id)
{

    Light *light;
    //LightControlContainerWidget *lcw;
    for (Light *l : g_lightMap.values())
    {
        if (l->getId() == id)
            light = l;
    }

    qDebug() << light->getId();

    QListWidget *widget = qobject_cast<QListWidget*>(sender());
    //    LightControlContainerWidget *widget = qobject_cast<LightControlContainerWidget*>(light->lcwWidget);

    int index = widget->currentItem()->data((Qt::UserRole)).toInt();
    qDebug() << index;
    if (index == 3)
        topWidget->setCurrentIndex(0);



    if (index == 1)
    {

        //this->topWidget->setCurrentWidget(parent->getLight()->presetWidget);
    }

    //contentLayout->setCurrentIndex(zoneButtons->currentItem()->data(Qt::UserRole).toInt());
    //this->zone.pageStack.append(contentLayout->currentWidget());
}
