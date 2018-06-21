#include <QLinearGradient>
#include <QBrush>
#include <QPicture>

#include "w_lightcontrolcontainer.h"
#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
#include "w_zonecontainer.h"
#include "mainwindow.h"
#include "tcpconnection.h"

extern TCPConnection *networkThread;

LightControlContainerWidget::LightControlContainerWidget(Zone zone, Light *light, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControlWidget)

{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);
    this->zone = zone;
    this->light = light;

    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->btnSelectPreset,0,0);

    HSVWheel *hsvWheel = new HSVWheel(this);
    hslSwatch = new HSLSwatch(this);

//    ZoneLightsWidget* myParent = dynamic_cast<ZoneLightsWidget*>(parent);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    rgb.setHsv(0,255,255);
    contentLayout->addWidget(hsvWheel,1,0,1,1);
    contentLayout->addWidget(hslSwatch,1,1,1,1);

    contentLayout->addWidget(preview,0,1,1,1);

    connect(hsvWheel,SIGNAL(colorChange(QColor)),this,SLOT(updateFromWheel(QColor)));
    connect(hslSwatch,SIGNAL(colorChange(QColor)),this,SLOT(updateFromSwatch(QColor)));
    this->btnShowPreset = new QPushButton(ui->btnSelectPreset);
}

LightControlContainerWidget::~LightControlContainerWidget()
{
    delete ui;
}

void LightControlContainerWidget::updateFromWheel(QColor qcol)
{
    rgb.setHsv(qcol.hue(),rgb.saturation(),rgb.value());
    hslSwatch->updateHue(qcol);
    hslSwatch->repaint();
    preview->color.setHsv(rgb.hue(),rgb.saturation(),rgb.value());
    preview->repaint();
    light->setColor(rgb.name().toUpper().replace("#","") + "FF");
}

void LightControlContainerWidget::updateFromSwatch(QColor qcol)
{
    rgb.setHsv(rgb.hue(), qcol.saturation(), qcol.value());
    preview->color.setHsv(rgb.hue(),rgb.saturation(),rgb.value());
    preview->repaint();
    light->setColor(rgb.name().toUpper().replace("#","") + "FF");
}
