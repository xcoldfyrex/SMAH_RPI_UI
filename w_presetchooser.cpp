#include <QPushButton>
#include "w_presetchooser.h"
#include "preset.h"
#include "zone.h"
#include <QDebug>

extern QList<Preset*> *gPresetList;
extern Zone *gActiveZone;
PresetChooser::PresetChooser(QWidget *parent) : QWidget(parent)
{
    MainWindow* mwParent = dynamic_cast<MainWindow*>(parent);
    this->mwParent = mwParent;

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
        QListWidgetItem *item = new QListWidgetItem();
        QVariant data(preset->id);
        item->setData(Qt::UserRole, data);
        item->setText(preset->getName());
        presetList->addItem(item);
    }
    presetList->setObjectName("presetList");
    connect(btnActivate,SIGNAL(clicked(bool)), this, SLOT(setPreset()));

}

void PresetChooser::setPreset() {
    int presetInt = this->presetList->currentItem()->data(Qt::UserRole).toInt();
    qDebug() << "Preset " << gActiveZone->name;
    gActiveZone->setActivePreset(presetInt);

    Preset *targetPreset;
    foreach (Preset *preset, *gPresetList) {
        if(presetInt == preset->id)
            targetPreset = preset;
    }

    QJsonObject jsonPayload;
    jsonPayload["type"] = "01";
    jsonPayload["value"] = targetPreset->getHex();
    this->mwParent->sendToNetwork("SET",jsonPayload);
}
