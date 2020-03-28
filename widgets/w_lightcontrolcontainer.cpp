#include <QLinearGradient>
#include <QBrush>
#include <QPicture>

#include "w_lightcontrolcontainer.h"
//#include "ui_lightcontrolwidget.h"
#include "w_hsvpalette.h"
#include "mainwindow.h"

LightControlContainerWidget::LightControlContainerWidget(Zone *zone, Light *light, QWidget *parent) :
    QWidget(parent)//,
    //ui(new Ui::LightControlWidget)

{
    //ui->setupUi(this);

    this->topWidget = new QWidget;
    this->contentLayout = new QHBoxLayout(topWidget);
    QVBoxLayout *rightItems = new QVBoxLayout();
    btnSetPreset = new QEngravedPushButton("Presets");
    btnSetOff = new QEngravedPushButton("Turn Off");
    btnBack = new QEngravedPushButton("Back");
    btnSetPreset->setObjectName("btnSetPreset");
    btnSetOff->setObjectName("btnSetOff");
    btnBack->setObjectName("btnBack");
    sl_whitelevel = new QSlider(Qt::Horizontal);
    sl_whitelevel->setMaximum(255);
    sl_whitelevel->setMinimum(0);
    sl_whitelevel->setMaximumWidth(500);



    //chkWhiteEnabled = new QCheckBox("White LED On");


    this->zone = zone;
    this->light = light;

    contentLayout->setContentsMargins(0,0,0,0);

    HSVWheel *colorPalette = new HSVWheel(this);

    preview = new ColorPreview(this);
    preview->color.setRgb(255,255,255);
    rgb.setHsv(0,255,255);

    contentLayout->addWidget(colorPalette);
    contentLayout->addWidget(preview);
    contentLayout->addLayout(rightItems);
    rightItems->addWidget(btnSetPreset,1, Qt::AlignLeft);
    rightItems->addWidget(btnSetOff,1, Qt::AlignLeft);
    rightItems->addWidget(btnBack,1, Qt::AlignLeft);

    //rightItems->addStretch(2);


    //rightItems->addWidget(chkWhiteEnabled);
    rightItems->addWidget(new QLabel("White Intensity"));
    rightItems->addWidget(sl_whitelevel);
    rightItems->addWidget(preview);


    connect(colorPalette,SIGNAL(colorChange(QColor)),this,SLOT(updateFromWheel(QColor)));
    connect(sl_whitelevel,SIGNAL(valueChanged(int)),this, SLOT(sliderChanged(int)));

    //btnBack->setMinimumWidth(btnSetPreset->width());
    //zoneButtons->setMinimumWidth(zoneButtons->sizeHintForColumn(0) + 20);

}

LightControlContainerWidget::~LightControlContainerWidget()
{
    //delete ui;
}

void LightControlContainerWidget::updateFromWheel(QColor qcol)
{
    QString white = QString::number(this->sl_whitelevel->value(), 16).toUpper();
    preview->color.setHsv(qcol.hue(),qcol.saturation(),qcol.value());
    preview->repaint();
    light->setColor(qcol.name().toUpper().replace("#","") + white, false);
}

void LightControlContainerWidget::sliderChanged(int val)
{
    QString white = QString::number(val, 16).toUpper();
    QString color = light->getColor();
    light->setColor(color + white, false);
}
