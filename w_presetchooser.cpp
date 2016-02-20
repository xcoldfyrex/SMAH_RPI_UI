#include <QPushButton>
#include "w_presetchooser.h"
#include "preset.h"
#include "zone.h"
#include <QDebug>


extern QList<Preset*> *gPresetList;
extern Zone *gActiveZone;
PresetChooser::PresetChooser(QWidget *parent) : QWidget(parent)
{
    QPushButton *btnActivate = new QPushButton(this);
    btnActivate->setText("Activate Preset");
    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QListWidget(this);
    presetList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    contentLayout->addStretch(1);
    contentLayout->addWidget(presetList);
    contentLayout->addWidget(btnActivate);
    foreach (Preset *preset, *gPresetList) {
        presetList->addItem(preset->getName());
    }
    presetList->setObjectName("presetList");
    connect(btnActivate,SIGNAL(clicked(bool)), this, SLOT(setPreset()));

}

void PresetChooser::setPreset() {
    qDebug() << "Preset " << this->presetList->currentItem()->text();
    //fix this....
    gActiveZone->setActivePreset(0);
}
