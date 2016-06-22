#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QJsonObject>

//#include "w_mainwindow.h"
#include "preset.h"

class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    explicit PresetChooser(QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *presetList;
    QVBoxLayout *contentLayout;
private:
    //MainWindow* mwParent;

signals:
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void setPreset();
    void addPreset(Preset *preset);
    void sendToNetwork(QString command, QJsonObject jsonPayload);
    void onListMailItemClicked(QListWidgetItem *item);

};

#endif // W_PRESETCHOOSER_H
