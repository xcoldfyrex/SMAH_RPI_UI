#include "w_lightcontrolcontainer.h"
#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
#include "w_brightnesspalette.h"
#include "w_colorpreview.h"
#include "w_zonecontainer.h"
#include "w_mainwindow.h"
#include <QLinearGradient>
#include <QBrush>
#include <QDebug>
#include <QPicture>

extern
LightControlContainerWidget::LightControlContainerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControlWidget)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->btnSelectPreset,0,0);
    contentLayout->addWidget(ui->lblActivePreset,0,2);

    HSVPalette *hsvSwatch = new HSVPalette(this);
    BrightnessPalette *brightness = new BrightnessPalette(this);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);

    contentLayout->addWidget(hsvSwatch,1,0,1,4);
    contentLayout->addWidget(brightness,2,0,1,4);
    contentLayout->addWidget(preview,3,0,1,4);    

    connect(hsvSwatch,SIGNAL(changed(QColor)),this,SLOT(updateHSVSelected(QColor)));
    connect(brightness,SIGNAL(changed(QColor)),this,SLOT(updateBrightnessSelected(QColor)));

    ZoneContainerWidget* myParent = dynamic_cast<ZoneContainerWidget*>(parent);
    MainWindow* mwParent = dynamic_cast<MainWindow*>(parent);
    this->mwParent = mwParent;

    connect(ui->btnSelectPreset,SIGNAL(clicked(bool)),myParent,SLOT(showPresetChooser()));


}

LightControlContainerWidget::~LightControlContainerWidget()
{
    delete ui;
}

void LightControlContainerWidget::updateHSVSelected(QColor qcol)
{

    this->rgb.setHsv(qcol.hue(),qcol.saturation(),this->preview->color.value());
    this->preview->color.setHsv(qcol.hue(),qcol.saturation(),this->rgb.value());
    this->preview->repaint();
    //qDebug() << "RGB"  << rgb.red() << rgb.green() << rgb.blue();

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = this->preview->color.name().replace("#","") + "FF";
    this->mwParent->sendToNetwork("SET",jsonPayload);
}

void LightControlContainerWidget::updateBrightnessSelected(QColor qcol)
{
    this->rgb.setHsv(this->rgb.hue(),this->rgb.saturation(),qcol.value());
    this->preview->color.setHsv(this->rgb.hue(),this->rgb.saturation(),qcol.value());

    qcol.setHsv(this->rgb.hue(),this->rgb.saturation(),qcol.value());
    //qDebug() << qcol.name();
    this->preview->repaint();

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = qcol.name().replace("#","") + "FF";
    this->mwParent->sendToNetwork("SET",jsonPayload);
}
