#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
        qWarning() << "Error: connection with database fail";
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createTable()
{
    bool success = false;

    QSqlQuery query;
    query.prepare("CREATE TABLE sensor_values(id INTEGER, temp INTEGER, rh INTEGER, lux INTEGER, ts LONG, PRIMARY KEY (ts, id));");

    return success;
}

bool DbManager::addValue(const int id, int temp, int rh, int lux,  quint64 ts)
{
    bool success = false;


        QSqlQuery queryAdd;
        // ID TEMP RH LUX TS
        queryAdd.prepare("CREATE TABLE sensor_values(id INTEGER, temp INTEGER, rh INTEGER, lux INTEGER, ts LONG, PRIMARY KEY (ts, id));");
        queryAdd.exec();

        queryAdd.prepare("REPLACE INTO sensor_values (id, temp, rh, lux, ts) VALUES (:id, :temp, :rh, :lux, :ts);");
        queryAdd.bindValue(":temp", temp);
        queryAdd.bindValue(":rh", rh);
        queryAdd.bindValue(":lux", lux);
        queryAdd.bindValue(":ts", ts);
        queryAdd.bindValue(":id", id);
        if(queryAdd.exec())
        {
            success = true;
            m_db.commit();
        }
        else
        {
            qWarning() << "Update failed: " << queryAdd.lastError();
        }    
    return success;
}

bool DbManager::addPondValue(int temp, float ph, quint64 ts)
{
    bool success = false;


    QSqlQuery queryAdd;
    queryAdd.prepare("CREATE TABLE pond_readings(temp INTEGER, ph FLOAT, ts LONG, PRIMARY KEY (ts));");
    queryAdd.exec();

    queryAdd.prepare("REPLACE INTO pond_readings (temp, ph, ts) VALUES (:temp, :ph, :ts);");
    queryAdd.bindValue(":temp", temp);
    queryAdd.bindValue(":ph", ph);
    queryAdd.bindValue(":ts", ts);
    if(queryAdd.exec())
    {
        success = true;
        m_db.commit();
    }
    else
    {
        qWarning() << "Update failed: " << queryAdd.lastError();
    }
    return success;
}

