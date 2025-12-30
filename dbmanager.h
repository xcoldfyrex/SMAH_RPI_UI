#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "qjsonobject.h"
#include "qsqlerror.h"
#include <QSqlDatabase>
#include <QSqlQuery>

class DbManager : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE QVariant search(QString mInputText) {
        if (!isOpen()) {
            qWarning() << "DB not open";
            return "";
        }
        QSqlQuery query;
        QList<QString> data;
        query.prepare(mInputText);
        if(!query.exec()) {
            qWarning() << "Query error" << query.lastError();
            qWarning() << mInputText;
            return "";
        }

        while(query.next() ) {
            data.append(query.value(0).toString() + "," + query.value(1).toString() + "," + query.value(2).toString());
        }
        if(query.first()) {
            return data;
        }
        else
            return "";
    }

    DbManager(const QString& path);
    ~DbManager();
    bool isOpen() const;
    bool createTable();

    bool addValue(const int id, int temp, int rh, int lux, quint64 ts);
    bool addPondValue(int temp, float ph, quint64 ts);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
