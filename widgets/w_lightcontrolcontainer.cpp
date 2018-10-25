#include <QLinearGradient>
#include <QBrush>
#include <QPicture>

#include "w_lightcontrolcontainer.h"
#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
#include "w_zonecontainer.h"
#include "mainwindow.h"

LightControlContainerWidget::LightControlContainerWidget(Zone zone, Light *light, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightControlWidget)

{
    ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QHBoxLayout(topWidget);
    QVBoxLayout *rightItems = new QVBoxLayout();
    btnSetPreset = new QPushButton("> Choose Preset");
    btnSetOff = new QPushButton("> Turn Off");
    btnBack = new QPushButton("> Back");
    btnSetPreset->setObjectName("btnSetPreset");
    btnSetOff->setObjectName("btnSetOff");
    btnBack->setObjectName("btnBack");
    chkWhiteEnabled = new QCheckBox("White LED On");


    this->zone = zone;
    this->light = light;

    contentLayout->setContentsMargins(0,0,0,0);

    HSVWheel *colorPalette = new HSVWheel(this);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    rgb.setHsv(0,255,255);

    contentLayout->addWidget(preview);
    contentLayout->addWidget(colorPalette);
    contentLayout->addLayout(rightItems);
    rightItems->addWidget(btnSetPreset,1, Qt::AlignLeft);
    rightItems->addWidget(btnSetOff,1, Qt::AlignLeft);
    rightItems->addWidget(btnBack,1, Qt::AlignLeft);
    rightItems->addStretch(1);
    rightItems->addWidget(chkWhiteEnabled);
    connect(colorPalette,SIGNAL(colorChange(QColor)),this,SLOT(updateFromWheel(QColor)));

    //btnBack->setMinimumWidth(btnSetPreset->width());
    //zoneButtons->setMinimumWidth(zoneButtons->sizeHintForColumn(0) + 20);

}

LightControlContainerWidget::~LightControlContainerWidget()
{
    delete ui;
}

void LightControlContainerWidget::updateFromWheel(QColor qcol)
{
    QString white = "00";
    if (this->chkWhiteEnabled->isChecked())
        white = "FF";
    preview->color.setHsv(qcol.hue(),qcol.saturation(),qcol.value());
    preview->repaint();
    light->setColor(qcol.name().toUpper().replace("#","") + white, false);
}
