#include <QPushButton>

#include "w_presetchooser.h"
#include "mainwindow.h"
#include "network.h"
#include "zone.h"

extern QList<Preset*> *gPresetList;
extern NetworkThread *networkThread;

PresetChooser::PresetChooser(Zone *zone, QWidget *parent) : QWidget(parent)
{
    QPushButton *btnActivate = new QPushButton(this);
    btnActivate->setText("Activate Preset");

    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QListWidget(this);
    this->zone = zone;

    contentLayout->addWidget(presetList);
    contentLayout->addWidget(btnActivate);

    presetList->setObjectName("presetList");

    connect(networkThread,SIGNAL(presetArrived(Preset*)), this, SLOT(addPreset(Preset*)));
    connect(btnActivate,SIGNAL(clicked(bool)), this, SLOT(setPreset()));
    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(presetList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setPreset()));
}

void PresetChooser::setPreset()
{
    int presetInt = this->presetList->currentItem()->data(Qt::UserRole).toInt();
    this->zone->setActivePreset(presetInt);

    Preset *targetPreset;
    foreach (Preset *preset, *gPresetList) {
        if(presetInt == preset->id)
            targetPreset = preset;
    }

    QJsonObject jsonPayload;
    jsonPayload["resource"] = "PRESET";
    jsonPayload["id"] = targetPreset->id;
    this->sendToNetwork("ACTIVATE",jsonPayload);
}

void PresetChooser::sendToNetwork(QString command, QJsonObject jsonPayload)
{
    jsonPayload["zone"] = this->zone->id;
    emit(requestingNetworkOut(command,jsonPayload, ""));
}

void PresetChooser::addPreset(Preset *preset)
{
    QListWidgetItem *item = new QListWidgetItem();
    QVariant data(preset->id);
    item->setData(Qt::UserRole, data);
    item->setText(preset->getName());
    presetList->addItem(item);
}
