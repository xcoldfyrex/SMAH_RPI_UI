#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>

#include <rpidevice.h>

class SystemSettings : public QWidget
{
    Q_OBJECT
public:
    explicit SystemSettings(QWidget *parent = nullptr);
    QWidget *topWidget;
    QGridLayout *contentLayout;

private:
    QListWidget *statusList;
    QListWidget *deviceList;

signals:

private slots:
    void reloadStyles();

public slots:
    void addDevice(RPIDevice device);
    void removeDevice(RPIDevice device);
};

#endif // SYSTEMSETTINGS_H
