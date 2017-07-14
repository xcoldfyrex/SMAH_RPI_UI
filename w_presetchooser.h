#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJsonObject>

#include "libsmah_preset.h"

class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    explicit PresetChooser(QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *presetList;
    QVBoxLayout *contentLayout;
private:

signals:
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void setPreset();
    void addPreset(Preset *preset);
    void sendToNetwork(QString command, QJsonObject jsonPayload);
};

#endif // W_PRESETCHOOSER_H
