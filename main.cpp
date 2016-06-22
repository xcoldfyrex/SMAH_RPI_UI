#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>

#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include "zone.h"
#include "preset.h"

QList<Zone*> *gZoneList;
QList<Preset*> *gPresetList;
Zone *gActiveZone = new Zone();
QTextEdit *txtLogger;
NetworkThread *networkThread;


int main(int argc, char *argv[])
{

    gZoneList = new QList<Zone*>();
    gPresetList = new QList<Preset*>();

    QApplication a(argc, argv);

    QFile File(QDir::currentPath()+"/../assets/main.css");
    qDebug() << "CWD: "<< QDir::currentPath();
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    QFontDatabase::addApplicationFont("../assets/Crescent-Regular.ttf");
    QFontDatabase::addApplicationFont("../assets/sui-generis-free.ttf");

    MainWindow mainWindow;
    qInstallMessageHandler(MainWindow::logHandler);
    mainWindow.show();

    return a.exec();
}
