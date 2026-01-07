#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QMap>
#include <QDateTime>
#include <QDate>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>

#include "dbmanager.h"
#include "qvariant.h"

extern int MY_DEVICE_ID;
extern DbManager *g_sqlDb;

typedef QMap<int, float> SensorValueMap;

Q_DECLARE_METATYPE(SensorValueMap)

class Sensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int getLux READ getLux NOTIFY luxChanged)
    Q_PROPERTY(QVariant temperature READ getTemperature NOTIFY valueChanged)
    Q_PROPERTY(QVariant rh READ getHumidity NOTIFY valueChanged)
    Q_PROPERTY(QVariant lux READ getLux NOTIFY valueChanged)
    Q_PROPERTY(QVariant uv READ getUV NOTIFY valueChanged)
    Q_PROPERTY(QVariant updated READ getLastUpdate NOTIFY valueChanged)
    Q_PROPERTY(SensorValueMap values READ getValues NOTIFY valueChanged)
    Q_PROPERTY(QString name READ getName CONSTANT)

public:
    Sensor();
    Sensor(QString name, int node_id, QObject *parent = nullptr);
    explicit Sensor(QObject *parent = nullptr);
    QVariant getTemperature() {
        return this->getValue(1);
    }
    float getLux() { return this->getValue(3); }
    float getHumidity() { return this->getValue(5); }
    float getUV() { return this->getValue(27); }
    int getNodeId() { return this->node_id; }
    qint64 getLastUpdate() { return this->updated; }
    void setLastUpdate(qint64 ts) { this->updated = ts; }

    QString getName() { return this->name; }

    //void setTemperatureFromRaw(float temperature);
    //void setHumidityFromRaw(float humidity);
    QMap<int, float> getValues() { return  this->values; }
    void setValue(int index, float value) {
        ///DbManager db(path);
        this->values[index] = value;
        setLastUpdate(QDateTime::currentSecsSinceEpoch());
        g_sqlDb->addValue(this->node_id, this->getTemperature().toInt(),this->getHumidity(),this->getLux(),(int(this->getLastUpdate() / 60)) * 60);
        ///db.addValue(index, value, this->getLastUpdate());
        emit(valueChanged());
    }
    float getValue(int index) {
        if (this->values.contains(index))
            return this->values[index];
        return 0;
    }

signals:
    void valueChanged();
    void temperatureChanged(float const temperature);
    void luxChanged(const float &lux);

private:        
    float humidity = 0; /* DEPRECATE THIS */
    //float raw_temperature = 0; /* DEPRECATE THIS */
    //float raw_humidity = 0;
    short lux = 0; /* DEPRECATE THIS */
    //short motion_level = 0;
    int battery = 0;
    int node_id;
    qint64 updated = 0;
    QString name;
    QMap<int, float> values;
};

#endif // SENSOR_H
