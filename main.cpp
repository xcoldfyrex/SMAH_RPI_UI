#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include "zone.h"
#include "network.h"

#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>

QList<Zone*> *gZoneList;
Zone *gActiveZone;

void loadZones()
{
    gZoneList = new QList<Zone*>();
    QDomDocument zoneXMLDocument;
    QFile zoneXMLFile(QDir::currentPath() + "/../assets/lights.xml");

    if (!zoneXMLDocument.setContent(&zoneXMLFile)) {
        qDebug() << "failed to open XML";
        return;
    }

    zoneXMLFile.close();

    QDomElement root = zoneXMLDocument.firstChildElement();
    QDomNodeList items = root.elementsByTagName("room");
    for (int i = 0; i < items.count(); i++) {
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()) {
            QDomElement element = itemnode.toElement();
            Zone *zone = new Zone(element.attribute("id").toInt(),element.attribute("name"),true,true,true);
            gZoneList->append(zone);
        }
    }
}

int main(int argc, char *argv[])
{
    loadZones();

    QApplication a(argc, argv);

    QFile File(QDir::currentPath()+"/../assets/main.css");
    qDebug() << "CWD: "<< QDir::currentPath();
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

    QFontDatabase::addApplicationFont("../assets/Crescent-Regular.ttf");
    QFontDatabase::addApplicationFont("../assets/sui-generis-free.ttf");

    MainWindow mainWindow;
    mainWindow.show();

    Network network;
    network.start("127.0.0.1", 9002);

    return a.exec();
}
