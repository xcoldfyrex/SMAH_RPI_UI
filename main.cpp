#include "menuwidget.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>


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

    QDomDocument document;
    QFile xmlDoc("/home/lenny/house/config/lights.xml");

    if (!document.setContent(&xmlDoc)) {
        qDebug() << "failed to open XML";
        return -1;
    }

    xmlDoc.close();

    QDomElement root = document.firstChildElement();
    QDomNodeList items = root.elementsByTagName("room");
    qDebug() << "Total " << items.count();

    for (int i = 0; i < items.count(); i++) {
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()) {
            QDomElement itemel = itemnode.toElement();
            qDebug() << itemel.attribute("name");
        }
    }

    return a.exec();
}
