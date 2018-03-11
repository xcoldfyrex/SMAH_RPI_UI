#include <QApplication>
#include <QDir>
#include <QStandardPaths>

#include "w_systemsettings.h"

SystemSettings::SystemSettings(QWidget *parent) : QWidget(parent)
{

    QPushButton *btnReloadStyles = new QPushButton("Reload Stylesheets");
    QPushButton *btnRefresh = new QPushButton("Refresh Objects");
    QSpacerItem *spacer2 = new QSpacerItem(1,1);

    //btnReloadStyles.setText("dsfsd");
    topWidget = new QWidget;
    contentLayout = new QGridLayout(topWidget);
    contentLayout->addWidget(btnReloadStyles,0,0);
    contentLayout->addWidget(btnRefresh,1,0);

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
