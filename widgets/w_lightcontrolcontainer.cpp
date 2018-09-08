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
    this->contentLayout = new QHBoxLayout(topWidget);
    QVBoxLayout *rightItems = new QVBoxLayout();

    this->zone = zone;
    this->light = light;

    zoneButtons = new QListWidget(this);
    QListWidgetItem *itemSetPreset = new QListWidgetItem("> Choose Preset");
    QListWidgetItem *itemSetOff = new QListWidgetItem("> Turn Off");
    QListWidgetItem *itemBack = new QListWidgetItem("> Back");

    itemSetPreset->setData(Qt::UserRole,1);
    itemSetOff->setData(Qt::UserRole,2);
    itemBack->setData(Qt::UserRole,3);
    zoneButtons->addItem(itemSetPreset);
    zoneButtons->addItem(itemSetOff);
    zoneButtons->addItem(itemBack);

    //btnSelectPreset = new QPushButton("Select Preset");
    contentLayout->setContentsMargins(0,0,0,0);
    //contentLayout->addWidget(btnSelectPreset,1,1);

    HSVWheel *colorPalette = new HSVWheel(this);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    rgb.setHsv(0,255,255);

    contentLayout->addWidget(preview);
    contentLayout->addWidget(colorPalette);
    contentLayout->addLayout(rightItems);
    rightItems->addWidget(zoneButtons,1, Qt::AlignRight);
    zoneButtons->setMinimumWidth(zoneButtons->sizeHintForColumn(0) + 20);
    connect(colorPalette,SIGNAL(colorChange(QColor)),this,SLOT(updateFromWheel(QColor)));
}

LightControlContainerWidget::~LightControlContainerWidget()
{
    delete ui;
}

void LightControlContainerWidget::updateFromWheel(QColor qcol)
{
    preview->color.setHsv(qcol.hue(),qcol.saturation(),qcol.value());
    preview->repaint();
    light->setColor(qcol.name().toUpper().replace("#","") + "FF");
}


