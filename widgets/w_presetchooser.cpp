#include <QPushButton>
#include <QPixmap>

#include "w_presetchooser.h"
#include "mainwindow.h"
#include "tcpconnection.h"

extern QMap<int, Preset> gColorPresetMap;
extern TCPConnection *networkThread;

PresetChooser::PresetChooser(Zone zone, Light *light, QWidget *parent) : QWidget(parent)
{
    QPushButton *btnActivate = new QPushButton(this);
    btnActivate->setText("Activate Preset");

    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QListWidget(this);
    this->zone = zone;
    this->light = light;
    presetList->setIconSize(QSize(512,32));
    for (Preset preset : gColorPresetMap)
    {
        QListWidgetItem *item = new QListWidgetItem();
        QVariant data(preset.id);

        item->setData(Qt::UserRole, data);
        item->setText(preset.getName());
        item->setIcon(QIcon(QPixmap::fromImage(preset.drawPreview())));
        item->setTextAlignment(Qt::AlignRight);
        presetList->addItem(item);
    }
    contentLayout->addWidget(presetList);
    contentLayout->addWidget(btnActivate);

    presetList->setObjectName("presetList");
    connect(btnActivate,SIGNAL(clicked(bool)), this, SLOT(setPreset()));
    //connect(this->zone,SIGNAL(requestingNetworkOut(QString, QJsonObject, QString)),networkThread,SLOT(prepareToSendWrapper(QString,QJsonObject,QString)),Qt::QueuedConnection);
    connect(presetList,SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(setPreset()));
}

void PresetChooser::setPreset()
{
    int presetInt = this->presetList->currentItem()->data(Qt::UserRole).toInt();

    foreach (Preset preset, gColorPresetMap) {
        if(presetInt == preset.id)
            light->setActivePreset(preset);
    }
}


