#include "menuwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include "zone.h"
#include <QList>

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
            Zone *zone = new Zone(element.attribute("id").toInt(),element.attribute("name").toLatin1().data(),true,true,true);
            qDebug() << element.attribute("name");
        }
    }
}

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    QFontDatabase::addApplicationFont("/home/lenny/house/assets/Crescent-Regular.ttf");
    QFontDatabase::addApplicationFont("/home/lenny/house/assets/sui-generis-free.ttf");

    MainWindow w;
    w.show();

    QFile File("/home/lenny/main.css");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    qApp->setStyleSheet(StyleSheet);

    loadZones();

    return a.exec();
}
