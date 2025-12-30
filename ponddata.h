#ifndef PONDDATA_H
#define PONDDATA_H

#include "dbmanager.h"
#include "qdatetime.h"
#include <QObject>

/* vals for sensors */
const int LOW_PH_CAL = 1880;
const int MID_PH_CAL = 1290;
const int HIGH_PH_CAL = 863;

const float RTD_DEFAULT_OFFSET_VOLTAGE_CONST = 1108.00;
// const float RTD_DEFAULT_OFFSET_VOLTAGE_CONST = 1072.90;

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

    float secondary_temp_correction(float vcal){
        return 5E-06*vcal*vcal - 0.0043*vcal - 0.2768;
    }

    float real_temp(float voltage_mV) {
        float vcal = (voltage_mV - RTD_DEFAULT_OFFSET_VOLTAGE_CONST);
        float temp_c = (0.109 * vcal) + secondary_temp_correction(vcal) ;
        float temp_f = (temp_c * 9/5) + 32;
        return temp_f;
    }

    float real_ph(float voltage_mV) {
        if (voltage_mV > MID_PH_CAL) { //high voltage = low ph
            return 7.0 - 3.0 / (LOW_PH_CAL - MID_PH_CAL) * (voltage_mV - MID_PH_CAL);
        } else {
            return 7.0 - 3.0 / (MID_PH_CAL - HIGH_PH_CAL) * (voltage_mV - MID_PH_CAL);
        }
    }

    void setTemperature(float val) {
        tempf = real_temp(val);
        /* only one db called needed */
        setLastUpdate(QDateTime::currentSecsSinceEpoch());
        emit updatedVal();
    }
    void setPH(float val) {
        ph = real_ph(val);
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
    qint64 updated = QDateTime::currentSecsSinceEpoch();
signals:
    void updatedVal();
};

#endif
