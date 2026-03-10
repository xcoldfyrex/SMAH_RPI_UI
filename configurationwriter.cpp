#include "configurationwriter.h"
#include "qdir.h"
#include <QXmlStreamWriter>

ConfigurationWriter::ConfigurationWriter() {}

void ConfigurationWriter::updateNodes(QString parent, QString filename, QVariantList data) {
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        return;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("config");

    for (QVariant &outerkey : data) {
        if (outerkey.canConvert<QVariantMap>()) {
            QVariantMap m = outerkey.value<QVariantMap>();

            stream.writeStartElement(parent);
            stream.writeAttribute("name", m.value("mName").toString());
            /* if there are multiple shellys, write as list */
            stream.writeAttribute("shellyid", m.value("mShellyID").toString());
            /*
             *  determine if these are singletons or members of a group
             *  each item is going to a list with a map
            */
            if (m.value("mElements").canConvert<QVariantList>()) {
                QVariantList innerlist = m.value("mElements").toList();
                for (QVariant innermap : innerlist) {
                    QVariantMap tempMap = innermap.toMap();
                    stream.writeStartElement(m.value("mElementName").toString());
                    for (auto [innerkey, innervalue] : tempMap.asKeyValueRange()) {
                        QString newkey = QString::fromStdString(innerkey.toStdString());
                        newkey.remove(0,1);
                        newkey = newkey.toLower();

                        stream.writeAttribute(newkey, innervalue.toString());
                    }
                    stream.writeEndElement();
                }
            }

            stream.writeEndElement();

        } else {
            qDebug() << "Cannot convert" << outerkey;
        }
    }
    stream.writeEndElement();
    stream.writeEndDocument();
}
