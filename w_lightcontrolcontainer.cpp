#include <QLinearGradient>
#include <QBrush>
#include <QDebug>
#include <QPicture>

#include "w_lightcontrolcontainer.h"
#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
#include "w_colorpreview.h"
#include "w_zonecontainer.h"
#include "w_mainwindow.h"
#include "network.h"

extern NetworkThread *networkThread;
extern Zone *gActiveZone;

LightControlContainerWidget::LightControlContainerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControlWidget)
{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QGridLayout(topWidget);

    contentLayout->setContentsMargins(0,0,0,0);
    contentLayout->addWidget(ui->btnSelectPreset,0,0);

    HSVPalette *hsvSwatch = new HSVPalette(this);
    ZoneContainerWidget* myParent = dynamic_cast<ZoneContainerWidget*>(parent);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    contentLayout->addWidget(hsvSwatch,1,0,1,4);
    contentLayout->addWidget(preview,6,0,1,4);

    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSend(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(hsvSwatch,SIGNAL(colorChange(QColor)),this,SLOT(updateHSVSelected(QColor)));
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

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = this->preview->color.name().toUpper().replace("#","") + "FF";
    this->sendToNetwork("SET",jsonPayload);
}

void LightControlContainerWidget::updateBrightnessSelected(int qcol)
{
    this->rgb.setHsv(this->rgb.hue(),this->rgb.saturation(),qcol);
    this->preview->color.setHsv(this->rgb.hue(),this->rgb.saturation(),qcol);
    this->preview->repaint();

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = rgb.name().toUpper().replace("#","") + "FF";
    this->sendToNetwork("SET",jsonPayload);
}

void LightControlContainerWidget::updateSaturationSelected(int qcol)
{
    this->rgb.setHsv(this->rgb.hue(),qcol,this->rgb.value());
    this->preview->color.setHsv(this->rgb.hue(),qcol,this->rgb.value());
    this->preview->repaint();

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = rgb.name().toUpper().replace("#","") + "FF";
    this->sendToNetwork("SET",jsonPayload);
}

void LightControlContainerWidget::sendToNetwork(QString command, QJsonObject jsonPayload) {
    char zoneString[3];
    sprintf(zoneString, "%d", gActiveZone->id);
    jsonPayload["zone"] = zoneString;
    emit(requestingNetworkOut(command,jsonPayload, ""));
}
