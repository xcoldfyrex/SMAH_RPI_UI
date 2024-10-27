#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QLabel>
#include "preset.h"
#include "presettask.h"
#include "zwavemanager.h"

#include <QDebug>

const int LIGHT_ZWAVE = 0;
const int LIGHT_ZWAVE_DIMMABLE = 1;
const int LIGHT_RGB_LED = 10;
const int LIGHT_RGBW_LED = 11;
const int LIGHT_RGB_INVIDIDUAL_ADDRESS = 12;
const int LIGHT_RGBW_INVIDIDUAL_ADDRESS = 13;
const int LIGHT_MACICLIGHT = 100;

extern int MY_DEVICE_ID;
extern uint32 g_homeId;


class Light : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QString getName READ getName CONSTANT)
    Q_PROPERTY(QString getColor READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int getType READ getType CONSTANT)
    Q_PROPERTY(int getLevel READ getLevel WRITE setLevel NOTIFY levelChanged)    

public:
    explicit Light(QObject *parent = nullptr);
    Light(int id, QString name, int type, int deviceid, uint32 home_id);
    Q_INVOKABLE int getType() const { return this->type ;}
    QString getName() const { return this->name; }
    uint32 getHome_id() { return this->home_id; }
    QString getColor() { return this->color; }
    int getId() { return this->id; }
    int getGetDeviceId() { return this->deviceid; }
    int getLevel() { return this->level; }
    bool getState() { return this->level; }

    bool wasLastUpdateLocal()
    {
        return this->localUpdate;
    }

    void setLastUpdateLocal(bool wasit)
    {
        this->localUpdate = wasit;
    }

    void initState()
    {
        bool checkstate = getZWaveState(this->id);
        updateLevel(checkstate);
    }
    QList<int> getColorFromPWM();
    void setColorShelly(QString color, bool keepActive);
    void updateLevel(int level);
    void sendUpdate();


signals:
    bool levelChanged(Light *light);
    bool colorChanged();
    void nameChanged();

public slots:
    Q_INVOKABLE void setColor(QString color, bool keepActive);
    Q_INVOKABLE void setColor(QString color);
    Q_INVOKABLE QString getWhiteLevel() { return this->whiteLevel; }
    Q_INVOKABLE void toggleState();
    Q_INVOKABLE void setActivePreset(Preset *preset);
    Q_INVOKABLE void setLevel(int level);

private slots:
    void colorStepAction(QColor color);

private:

    int id, type, deviceid;
    int level = 0;
    bool state = 0;
    bool localUpdate = false;

    QString name;
    uint32 home_id;
    QString whiteLevel = "00";
    QString color = "000000";    
    QList<PresetTask*> *taskList;
};

//Q_DECLARE_METATYPE(Light)


#endif // LIGHT_H
