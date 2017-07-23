#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>

#include "zone.h"
#include "w_zonechooser.h"
#include "mainwindow.h"
#include "libsmah_preset.h"
#include "libsmah.h"


QMap<int, Zone*> *gZoneMap;
QList<Preset*> *gPresetList;
NetworkThread *networkThread;

int main(int argc, char *argv[])
{
    gZoneMap = new QMap<int, Zone*>();
    gPresetList = new QList<Preset*>();

    QApplication a(argc, argv);
    qInstallMessageHandler(systemlogHandler);

    QString homeLocation = QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory);
    QDir::setCurrent(homeLocation + "/.smah/assets");

    QFile File("main.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    QFontDatabase::addApplicationFont("Crescent-Regular.ttf");
    QFontDatabase::addApplicationFont("sui-generis-free.ttf");

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
