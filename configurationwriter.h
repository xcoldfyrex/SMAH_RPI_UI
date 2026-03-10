#ifndef CONFIGURATIONWRITER_H
#define CONFIGURATIONWRITER_H

#include <QObject>
#include <QMap>
#include <QVariant>

class ConfigurationWriter : public QObject
{
    Q_OBJECT
public:
    ConfigurationWriter();
    //Q_INVOKABLE void updateNodes(QString parent, QList<QVariant> data);
    Q_INVOKABLE void updateNodes(QString parent, QString filename, QVariantList data);


};

#endif // CONFIGURATIONWRITER_H
