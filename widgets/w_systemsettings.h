#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>

#include <rpidevice.h>
#include "qengravedlabel.h"


class SystemSettings : public QWidget
{
    Q_OBJECT
public:
    explicit SystemSettings(QWidget *parent = nullptr);
    QWidget *topWidget;
    QGridLayout *contentLayout;

private:
    QEngravedList *statusList;
    QEngravedList *deviceList;

signals:

private slots:
    void reloadStyles();
};

#endif // SYSTEMSETTINGS_H
