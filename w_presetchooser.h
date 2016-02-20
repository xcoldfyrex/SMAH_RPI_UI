#ifndef W_PRESETCHOOSER_H
#define W_PRESETCHOOSER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>


class PresetChooser : public QWidget
{
    Q_OBJECT
public:
    explicit PresetChooser(QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *presetList;
    QVBoxLayout *contentLayout;

signals:

public slots:

private slots:
    void setPreset();
};

#endif // W_PRESETCHOOSER_H
