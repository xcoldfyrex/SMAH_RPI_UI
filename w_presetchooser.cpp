#include "w_presetchooser.h"
#include "preset.h"

extern QList<Preset*> *gPresetList;

PresetChooser::PresetChooser(QWidget *parent) : QWidget(parent)
{
    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QListWidget(this);
    contentLayout->addStretch(1);

    contentLayout->addWidget(presetList);
    foreach (Preset *preset, *gPresetList) {
        presetList->addItem(preset->getName());
    }
    presetList->setObjectName("presetList");
    contentLayout->addStretch(1);
}
