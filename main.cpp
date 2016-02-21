#include "w_zonechooser.h"
#include "w_mainwindow.h"
#include "zone.h"
#include "network.h"
#include "preset.h"

#include <QApplication>
#include <QFile>
#include <QtGui>
#include <QFontDatabase>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QList>
#include <QDir>

QList<Zone*> *gZoneList;
QList<Preset*> *gPresetList;
Zone *gActiveZone = new Zone();
QTextEdit *txtLogger;
NetworkThread *networkConnection = new NetworkThread();


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

void loadPresets()
{
    gPresetList = new QList<Preset*>();
    QDomDocument zoneXMLDocument;
    QFile zoneXMLFile(QDir::currentPath() + "/../assets/light_presets.xml");

    if (!zoneXMLDocument.setContent(&zoneXMLFile)) {
        qDebug() << "failed to open XML";
        return;
    }

    zoneXMLFile.close();

    QDomElement root = zoneXMLDocument.firstChildElement();
    QDomNodeList items = root.elementsByTagName("static");
    short presetID = 0;
    for (int i = 0; i < items.count(); i++) {
        QDomNode itemnode = items.at(i);
        if (itemnode.isElement()) {
            QDomElement presetElement = itemnode.toElement();
            QString staticCode = presetElement.attribute("code");
            if (staticCode.length() != 8) {
                qDebug() << "Invalid code: " << staticCode;
            } else {
                Preset *preset = new Preset(presetElement.attribute("name"),presetID);
                presetID++;
                preset->setColor(staticCode);
                gPresetList->append(preset);
                qDebug() << "Loaded preset " << presetElement.attribute("name") << staticCode ;

            }
        }
    }
}

int main(int argc, char *argv[])
{
    loadZones();
    loadPresets();

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
    mainWindow.startNetworking();

    return a.exec();
}
