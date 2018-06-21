#include <QApplication>
#include <QDir>
#include <QStandardPaths>
#include <QLabel>

#include "w_systemsettings.h"
#include "tcpconnection.h"
#include "build_number.h"
extern TCPConnection networkThread;

SystemSettings::SystemSettings(QWidget *parent) : QWidget(parent)
{

    QPushButton *btnReloadStyles = new QPushButton("Reload Stylesheets");
    QPushButton *btnRefresh = new QPushButton("Refresh Objects");
    //QSpacerItem *spacer2 = new QSpacerItem(1,1);
    QPushButton *btnViewClient = new QPushButton("Connected Devices");
    QPushButton *btnPresets = new QPushButton("Known presets");

    const QString str_ip = "IP Address: " + networkThread.getIp_addr();
    QLabel *lblIP = new QLabel(str_ip);
    QLabel *lblBuild = new QLabel("Build number: " + QString::number(BUILD));


    //btnReloadStyles.setText("dsfsd");
    topWidget = new QWidget;
    contentLayout = new QGridLayout(topWidget);
    contentLayout->addWidget(lblBuild,0,0);
    contentLayout->addWidget(lblIP,1,0);
    contentLayout->addWidget(btnReloadStyles,0,1);
    contentLayout->addWidget(btnRefresh,1,1);
    contentLayout->addWidget(btnViewClient,2,1);
    contentLayout->addWidget(btnPresets,3,1);

    connect(btnReloadStyles,SIGNAL(clicked(bool)),this,SLOT(reloadStyles()));

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
