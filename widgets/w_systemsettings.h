#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class SystemSettings : public QWidget
{
    Q_OBJECT
public:
    explicit SystemSettings(QWidget *parent = 0);
    QWidget *topWidget;
    QGridLayout *contentLayout;

private:

signals:

private slots:
    void reloadStyles();
};

#endif // SYSTEMSETTINGS_H
