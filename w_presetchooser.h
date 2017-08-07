#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJsonObject>

#include "libsmah_preset.h"
#include "zone.h"

class Zone;

class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    explicit PresetChooser(Zone *zone, QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *presetList;
    QVBoxLayout *contentLayout;
private:
    Zone *zone;

public slots:
    void setPreset();

private slots:
    void addPreset(Preset preset);
};

#endif // W_PRESETCHOOSER_H
