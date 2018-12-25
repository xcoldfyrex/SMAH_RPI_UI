#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QListWidgetItem>
#include <QPushButton>

#include "preset.h"
#include "zone.h"
#include "light.h"

class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    PresetChooser(Zone zone, Light *light, QWidget *parent = nullptr);
    QWidget *topWidget;
    QListWidget *presetList;
    QListWidget *presetButtons;
    QPushButton *btnBack;
    QVBoxLayout *contentLayout;
private:
    Zone zone;
    Light *light;

public slots:
    void setPreset();

signals:
    void presetActivation(Preset preset);
};

#endif // W_PRESETCHOOSER_H
