#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QLabel>
#include "preset.h"
#include "presettask.h"
#include "shellyrelay.h"
#include "shellyrgbw.h"
#include <variant>
#include <any>
#include <QDebug>

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
    Q_PROPERTY(QString getName READ getName CONSTANT)
    Q_PROPERTY(QString getColor READ getColor WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(int getType READ getType CONSTANT)
    //Q_PROPERTY(int getLevel READ getLevel WRITE setLevel NOTIFY levelChanged)

public:
    Q_INVOKABLE
    explicit Light(QObject *parent = nullptr);

    Light(int id, QString name, int type, ShellyRGBW *shellydevice);
    Light(int id, QString name, int type, ShellyRelay *shellydevice);
    Light<ShellyRGBW>(int id, QString name, int type, T*);


    //Light<ShellyRGBW>(int id, QString name, int type, T*);

    Q_INVOKABLE int getType() const { return this->type ;}
    QString getName() const { return this->name; }
    QString getColor() { return this->color; }
    int getId() { return this->id; }
    QString getGetDeviceId() { return this->shelly->getID(); }
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

private slots:
    void colorStepAction(QColor color);

private:

    int id, type;
    int level = 0;
    bool state = 0;
    bool localUpdate = false;

    QString name;
    Shelly *shelly;
    //std::any *shellydevice;
    QString whiteLevel = "00";
    QString color = "000000";    
    QList<PresetTask*> *taskList;
};

//Q_DECLARE_METATYPE(Light)


#endif // LIGHT_H
