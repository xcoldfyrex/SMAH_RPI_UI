#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>
#include <QListWidget>

#include "w_systemsettings.h"
#include "build_number.h"

extern QString MY_HW_ADDR;
extern QString MY_IP_ADDR;

SystemSettings::SystemSettings(QWidget *parent) : QWidget(parent)
{

    //QPushButton *btnReloadStyles = new QPushButton("Reload Stylesheets");
    //QPushButton *btnRefresh = new QPushButton("Refresh Objects");
    //QSpacerItem *spacer2 = new QSpacerItem(1,1);
    //QPushButton *btnViewClient = new QPushButton("Connected Devices");
    //QPushButton *btnPresets = new QPushButton("Known presets");
    QListWidget *statusList = new QListWidget(this);
    QListWidget *buttonList = new QListWidget(this);

    statusList->setObjectName("labelList");
    statusList->setEnabled(false);

    const QString str_ip = "IP Address: " + MY_IP_ADDR;
    QString mac = "MAC Address: " + MY_HW_ADDR;


    QListWidgetItem *lblBuild = new QListWidgetItem("Build number: " + QString::number(BUILD));
    QListWidgetItem *lblBuildDate = new QListWidgetItem("Build date: " + QString(DATE));
    QListWidgetItem *lblIP = new QListWidgetItem(str_ip);
    QListWidgetItem *lblMAC = new QListWidgetItem(mac);
    statusList->addItem(lblBuild);
    statusList->addItem(lblBuildDate);
    statusList->addItem(lblIP);
    statusList->addItem(lblMAC);

    QListWidgetItem *itemReloadStyles = new QListWidgetItem("Reload Stylesheets");
    buttonList->addItem(itemReloadStyles);
    QListWidgetItem *itemConnectedDevices = new QListWidgetItem("Connected Devices");
    buttonList->addItem(itemConnectedDevices);
    QListWidgetItem *itemViewPresets = new QListWidgetItem("View Presets");
    buttonList->addItem(itemViewPresets);

    topWidget = new QWidget;
    contentLayout = new QGridLayout(topWidget);
    contentLayout->addWidget(statusList,0,0);
    contentLayout->addWidget(buttonList,0,1);
    //contentLayout->addWidget(btnReloadStyles,0,1);
    //contentLayout->addWidget(btnRefresh,1,1);
    //contentLayout->addWidget(btnViewClient,2,1);
    //contentLayout->addWidget(btnPresets,3,1);

    //connect(btnReloadStyles,SIGNAL(clicked(bool)),this,SLOT(reloadStyles()));

}

void SystemSettings::reloadStyles()
{
    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QDir::setCurrent(homeLocation + "/.smah/assets");

    QFile File("main.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);
}
