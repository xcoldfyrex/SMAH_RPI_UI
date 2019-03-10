#include <QPushButton>
#include <QPixmap>
#include <QScrollBar>
#include "w_presetchooser.h"
#include "mainwindow.h"

extern QMap<int, Preset> gColorPresetMap;

PresetChooser::PresetChooser(Zone zone, Light *light, QWidget *parent) : QWidget(parent)
{

    presetButtons = new QEngravedList(this);
    presetButtons->setObjectName("presetButtons");
    QListWidgetItem *itemBack = new QListWidgetItem("> Back");
    itemBack->setData(Qt::UserRole,1);
    presetButtons->addItem(itemBack);

    btnBack = new QEngravedPushButton("> BACK");
    btnBack->setObjectName("btnBack");

    this->topWidget = new QWidget;
    this->contentLayout = new QVBoxLayout(topWidget);
    this->presetList = new QEngravedList(this);
    this->zone = zone;
    this->light = light;
    presetList->setIconSize(QSize(512,32));
    QScrollBar *sb = new QScrollBar();
    sb->setPageStep(10);
    presetList->setVerticalScrollBar(sb);
    presetList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
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
    contentLayout->addWidget(btnBack,1, Qt::AlignRight);

    presetList->setObjectName("presetList");    
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

