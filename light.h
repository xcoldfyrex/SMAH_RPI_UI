#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QLabel>
#include "preset.h"
#include "presettask.h"
#include "zwavemanager.h"

const int LIGHT_ZWAVE = 0;
const int LIGHT_ZWAVE_DIMMABLE = 1;
const int LIGHT_RGB_LED = 10;
const int LIGHT_RGBW_LED = 11;
const int LIGHT_RGB_INVIDIDUAL_ADDRESS = 12;
const int LIGHT_RGBW_INVIDIDUAL_ADDRESS = 13;
const int LIGHT_MACICLIGHT = 100;

extern int MY_DEVICE_ID;

class Light : public QObject
{
    Q_OBJECT
public:
    explicit Light(QObject *parent = nullptr);
    Light(int id, QString name, int type, int deviceid);
    QString getName() const { return this->name; }
    int getType() const { return this->type ;}
    QString getColor() { return this->color; }
    int getId() { return this->id; }
    int getGetDeviceId() { return this->deviceid; }
    bool getState() { return this->level; }
    bool isLocal() {
        if (this->deviceid == MY_DEVICE_ID)
            return true;
        return false;
    }

    bool wasLastUpdateLocal()
    {
        return this->localUpdate;
    }

    void setLastUpdateLocal(bool wasit)
    {
        this->localUpdate = wasit;
    }

    QLabel *statusLabel;
    void initState()
    {
        bool checkstate = getZWaveState(this->id);
        updateLevel(checkstate);
    }
    QString getColorFromPWM();
    void setColorInPWM(QString color);
    void updateLevel(int level);
    void sendUpdate();


signals:
    bool levelChanged(Light *light);

public slots:
    void setColor(QString color);
    void toggleState();
    void setActivePreset(Preset preset);

private slots:
    void colorStepAction(QColor color);

private:
    int id, type, deviceid;
    QList<PresetTask*> *taskList;
    QString name;
    bool state = 0;
    int level = 0;
    QString color;
    bool localUpdate = false;
};

#endif // LIGHT_H
