#ifndef PONDDATA_H
#define PONDDATA_H

#include "dbmanager.h"
#include "qdatetime.h"
#include <QObject>

extern DbManager *g_sqlDb;

class PondData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float ph READ getPH NOTIFY updatedVal)
    Q_PROPERTY(float temp READ getTemperature NOTIFY updatedVal)
    Q_PROPERTY(QVariant updated READ getLastUpdate NOTIFY updatedVal)



public:
    explicit PondData();
    float getTemperature() { return tempf; }
    float getPH() { return ph; }
    void setTemperature(float val) {
        tempf = val;
        setLastUpdate(QDateTime::currentSecsSinceEpoch());
        emit updatedVal();
    }
    void setPH(float val) {
        ph = val;
        setLastUpdate(QDateTime::currentSecsSinceEpoch());
        emit updatedVal();
    }
    qint64 getLastUpdate() { return this->updated; }
    void setLastUpdate(qint64 ts) {
        this->updated = ts;
        if (this->tempf  > 32) {
            g_sqlDb->addPondValue(int(this->tempf), this->ph,(int(this->getLastUpdate() / 60)) * 60);
        } else {
            qWarning() << "Out of range value" << tempf;
        }
    }

private:
    float tempf = 0;
    float ph = 0;
    qint64 updated = 0;
signals:
    void updatedVal();
};

#endif
