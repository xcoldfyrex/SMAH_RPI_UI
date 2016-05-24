#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "w_mainwindow.h"

class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    explicit PresetChooser(QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *presetList;
    QVBoxLayout *contentLayout;
private:
    MainWindow* mwParent;

signals:

public slots:

private slots:
    void setPreset();
};

#endif // W_PRESETCHOOSER_H
