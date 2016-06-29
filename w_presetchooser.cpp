#include <QPushButton>
#include <QDebug>

#include "w_presetchooser.h"
#include "zone.h"
#include "network.h"

extern QList<Preset*> *gPresetList;
extern Zone *gActiveZone;
extern NetworkThread *networkThread;

PresetChooser::PresetChooser(QWidget *parent) : QWidget(parent)
{
    QPushButton *btnActivate = new QPushButton(this);
    btnActivate->setText("Activate Preset");

    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QListWidget(this);

    contentLayout->addWidget(presetList);
    contentLayout->addWidget(btnActivate);

    presetList->setObjectName("presetList");

    connect(btnActivate,SIGNAL(clicked(bool)), this, SLOT(setPreset()));
    connect(this,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSend(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(presetList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setPreset()));
}

void PresetChooser::setPreset()
{
    int presetInt = this->presetList->currentItem()->data(Qt::UserRole).toInt();
    gActiveZone->setActivePreset(presetInt);

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

void PresetChooser::addPreset(Preset *preset)
{

    QListWidgetItem *item = new QListWidgetItem();
    QVariant data(preset->id);
    item->setData(Qt::UserRole, data);
    item->setText(preset->getName());
    presetList->addItem(item);
    gPresetList->append(preset);
}


void PresetChooser::sendToNetwork(QString command, QJsonObject jsonPayload)
{
    char zoneString[3];
    sprintf(zoneString, "%d", gActiveZone->id);
    jsonPayload["zone"] = zoneString;
    emit(requestingNetworkOut(command,jsonPayload, ""));
}
