#include "light.h"

#include <QDebug>

//extern QMap <QString, RPIDevice> g_deviceList;
extern QString MY_HW_ADDR;
extern int MY_DEVICE_ID;

//Q_DECLARE_METATYPE(Light)

Light::Light(QObject *parent) : QObject(parent)
{
}

Light::Light(int id, QString name, int type, int deviceid)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->deviceid = deviceid;
    this->taskList = new QList<PresetTask*>();
}

//toggle a binary device
// TODO 10-20-2024 - probably unused now
void Light::toggleState()
{
    //do shit to send to network
    //QJsonObject jsonPayload;
    //jsonPayload["id"] = this->id;
    //ClientSocket *sock = determineZone(this);
    //if (!sock) {
    // pray and broadcast. need to send to proper home_id
    //tcpServer.broadcastMessageJSON("TOGGLE", jsonPayload);
    return;
    //}
    //sock->prepareToSend("TOGGLE", jsonPayload);
}

//set an RGBW device
void Light::setColor(QString color)
{
    setColor(color, false);
}

void Light::setColor(QString color, bool keepActive)
{
    this->color = color.mid(0,6);
    this->whiteLevel = color.mid(6,2);
    setColorShelly(color, keepActive);
    emit colorChanged();
}

// callback for when something happened
void Light::updateLevel(int level)
{
    this->level = level;
    QString text = "OFF";
    if (this->type == LIGHT_ZWAVE)
    {
        if (level == 1)
            text = "ON";
        //this->statusLabel = text;
    }

    if (this->type == LIGHT_ZWAVE_DIMMABLE)
    {
        text = QString::number(level) + '%';
        //this->statusLabel = text;
    }
}


// from an active preset - next color
void Light::colorStepAction(QColor color)
{
    setColor(color.name().toUpper().replace("#",""), true);
}

//toggle single rgb(w) strip
void Light::setColorShelly(QString color, bool keepActive = true)
{
    if (!keepActive)
    {
        if (this->taskList->length() > 0){
            PresetTask *toTerm;
            foreach (toTerm, *this->taskList) {
                toTerm->abortFlag = true;
            }
        }
        this->taskList->clear();
    }
    bool ok;
    short r = color.mid(0,2).toShort(&ok, 16);
    short g = color.mid(2,2).toShort(&ok, 16);
    short b = color.mid(4,2).toShort(&ok, 16);
    short w = color.mid(6,2).toShort(&ok, 16);

    // devices not on i2c device
    //gpioPWM(GPIO_PIN_RED, static_cast<uint>(r));
    //gpioPWM(GPIO_PIN_GREEN, static_cast<uint>(g));
    //gpioPWM(GPIO_PIN_BLUE, static_cast<uint>(b));
    //gpioPWM(GPIO_PIN_WHITE, static_cast<uint>(w));
    // well, it's on a fucking i2c bus.
    // also matt is a fucking wanker and sj is a troglodite
    //pca.setPWM((this->pwmbank - 1) * 4 + 1, r * 10);
    //pca.setPWM((this->pwmbank - 1) * 4 + 2, g * 10);
    //pca.setPWM((this->pwmbank - 1) * 4 + 3, b * 10);
    //pca.setPWM((this->pwmbank - 1) * 4 + 4, w * 10);

}



void Light::setActivePreset(Preset *preset)
{
    //gColorPresetMap.value(value)
    // a new preset and it's local. kill any tasks
    if (this->taskList->length() > 0){
        PresetTask *toTerm;
        foreach (toTerm, *this->taskList) {
            toTerm->abortFlag = true;
        }
    }
    this->taskList->clear();

    if (!preset->dynamic)
    {
        if (preset->type == 2){

        } else {
            setColor(preset->getHex());
        }
    } else {
        PresetTask *task = new PresetTask(preset);
        this->taskList->append(task);
        task->start();
        connect(task,SIGNAL(colorStepChanged(QColor)), this,SLOT(colorStepAction(QColor)));
    }
}

