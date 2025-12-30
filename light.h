#ifndef LIGHT_H
#define LIGHT_H

#include <QObject>
#include <QString>
#include <QColor>
#include <QLabel>
#include "preset.h"
#include "presettask.h"
#include "shelly.h"

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
    Q_PROPERTY(QString getColor READ getColor WRITE setColor NOTIFY colorChanged())
    Q_PROPERTY(QString getType READ getType NOTIFY stateChanged())
    Q_PROPERTY(bool getState READ getState NOTIFY stateChanged())
    Q_PROPERTY(int getBrightness READ getBrightness NOTIFY stateChanged())

public:
    Q_INVOKABLE
    explicit Light(QObject *parent = nullptr);
    Light(int id, QString name, Shelly *shellydevice);
    Q_INVOKABLE QString getType() { return this->type ;}
    Q_INVOKABLE bool getState() { return this->shellydevice->getState(); }
    Q_INVOKABLE int getBrightness() { return this->shellydevice->getBrightness(); }
    QString getName() const { return this->name; }
    QString getColor() { return this->color; }
    QString getGetDeviceId() { return this->shellydevice->getID(); }

    int getId() { return this->id; }
    int getLevel() { return this->level; }

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
    void setStateShelly(bool state);
    void setBrightnessShelly(int brightness);
    void sendUpdate();


signals:
    bool levelChanged(Light *light);
    bool colorChanged();
    bool stateChanged();
    void nameChanged();

public slots:
    Q_INVOKABLE void setColor(QString color, bool keepActive);
    Q_INVOKABLE void setColor(QString color);
    Q_INVOKABLE void setState(bool state) { setStateShelly(state); };
    Q_INVOKABLE void setBrightness(int brightness) { setBrightnessShelly(brightness); };

    Q_INVOKABLE QString getWhiteLevel() { return this->whiteLevel; }
    Q_INVOKABLE void toggleState();
    Q_INVOKABLE void setActivePreset(Preset *preset);

private slots:
    void colorStepAction(QColor color);

private:

    int id;
    int level = 0;
    bool state = false;
    bool localUpdate = false;

    QString name, type;
    Shelly *shellydevice;
    QString whiteLevel = "00";
    QString color = "000000";    
    QList<PresetTask*> *taskList;
};

//Q_DECLARE_METATYPE(Light)


#endif // LIGHT_H
