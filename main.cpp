#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include "zone.h"
#include <QList>
#include <QDir>

QList<Zone*> *zoneList = new QList<Zone*>();
QString activeZone;

void loadZones()
{
    QDomDocument zoneXMLDocument;
    QFile zoneXMLFile("/home/lenny/house/config/lights.xml");

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
            zoneList->append(zone);
        }
    }
}

int main(int argc, char *argv[])
{
    activeZone = "NA";
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


    return a.exec();
}
