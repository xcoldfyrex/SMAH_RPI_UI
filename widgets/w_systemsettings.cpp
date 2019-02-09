#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>

#include "w_systemsettings.h"
#include "build_number.h"
#include "tcpserver.h"

extern QString MY_HW_ADDR;
extern QString MY_IP_ADDR;
extern TCPServer tcpServer;

SystemSettings::SystemSettings(QWidget *parent) : QWidget(parent)
{
    statusList = new QListWidget(this);
    deviceList = new QListWidget(this);

    statusList->setObjectName("labelList");
    statusList->setEnabled(false);
    deviceList->setObjectName("labelList");
    deviceList->setEnabled(false);

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

    topWidget = new QWidget;
    contentLayout = new QGridLayout(topWidget);
    contentLayout->addWidget(new QLabel("status"),0,0);
    contentLayout->addWidget(new QLabel("devices"),0,1);
    contentLayout->addWidget(statusList,1,0);
    contentLayout->addWidget(deviceList,1,1);

    connect(&tcpServer,SIGNAL(deviceReady(RPIDevice)),this,SLOT(addDevice(RPIDevice)));
    connect(&tcpServer,SIGNAL(deviceLost(RPIDevice)),this,SLOT(removeDevice(RPIDevice)));
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

void SystemSettings::addDevice(RPIDevice device)
{
    QListWidgetItem *itemDevice = new QListWidgetItem(device.getName() + " " + device.getIP());
    QVariant dataitemConnectedDevice(device.getHwAddress());
    itemDevice->setData(Qt::UserRole, dataitemConnectedDevice);
    this->deviceList->addItem(itemDevice);
}

void SystemSettings::removeDevice(RPIDevice device)
{
//    this->deviceList->re
    int x;
}
