#include <QLinearGradient>
#include <QBrush>
#include <QPicture>

#include "w_lightcontrolcontainer.h"
#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
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

    HSVWheel *hsvWheel = new HSVWheel(this);
    hslSwatch = new HSLSwatch(this);

    ZoneContainerWidget* myParent = dynamic_cast<ZoneContainerWidget*>(parent);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    rgb.setHsv(0,255,255);
    contentLayout->addWidget(hsvWheel,1,0,1,1);
    contentLayout->addWidget(hslSwatch,1,1,1,1);

    contentLayout->addWidget(preview,0,1,1,1);

    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(hsvWheel,SIGNAL(colorChange(QColor)),this,SLOT(updateFromWheel(QColor)));
    connect(hslSwatch,SIGNAL(colorChange(QColor)),this,SLOT(updateFromSwatch(QColor)));

    connect(ui->btnSelectPreset,SIGNAL(clicked(bool)),myParent,SLOT(showPresetChooser()));


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

    QJsonObject jsonPayload;
    jsonPayload["type"] = 01;
    jsonPayload["value"] = rgb.name().toUpper().replace("#","") + "FF";
    sendToNetwork("SET",jsonPayload);
}

void LightControlContainerWidget::updateFromSwatch(QColor qcol)
{
    rgb.setHsv(rgb.hue(), qcol.saturation(), qcol.value());
    preview->color.setHsv(rgb.hue(),rgb.saturation(),rgb.value());
    preview->repaint();

    QJsonObject jsonPayload;
    jsonPayload["type"] = 01;
    jsonPayload["value"] = rgb.name().toUpper().replace("#","") + "FF";
    sendToNetwork("SET",jsonPayload);
}


void LightControlContainerWidget::sendToNetwork(QString command, QJsonObject jsonPayload) {
    char zoneString[3];
    sprintf(zoneString, "%d", gActiveZone->id);
    jsonPayload["zone"] = gActiveZone->id;
    emit(requestingNetworkOut(command,jsonPayload, ""));
}
