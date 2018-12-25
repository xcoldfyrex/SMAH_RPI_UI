#include "light.h"
#include "pigpio.h"
#include "gpio_defs.h"
#include "commandrouter.h"
#include "pca9685.h"

#include <QDebug>
extern QMap <QString, RPIDevice> g_deviceList;
extern QString MY_HW_ADDR;
extern int MY_DEVICE_ID;
extern smah_i2c bus;

Light::Light(QObject *parent) : QObject(parent)
{
    this->statusLabel = new QLabel("N/A");
}

Light::Light(int id, QString name, int type, int deviceid, short bank)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->statusLabel = new QLabel("N/A");
    this->deviceid = deviceid;
    this->taskList = new QList<PresetTask*>();
    this->pwmbank = bank;
}

//toggle a binary device
void Light::toggleState()
{
    if (this->isLocal())
    {
        // updates are done via the callback from the zwave driver
        bool state = getZWaveState(this->id);
        bool newstate;
        (state == false) ? (newstate = true) : (newstate = false);
        setZWaveToggle(newstate, this->id);
        qDebug() << "TOGGLE LOCAL";
    } else {
        //do shit to send to network
        ClientSocket *sock = determineZone(this);
        if (!sock)
            return;
        QJsonObject jsonPayload;
        jsonPayload["id"] = this->id;
        sock->prepareToSend("TOGGLE", jsonPayload);
    }

}

//set an RGBW device
void Light::setColor(QString color, bool keepActive = false)
{
    this->color = color.mid(0,6);
    this->whiteLevel = color.mid(6,2);

    if (this->isLocal())
    {
        setColorInPWM(color, keepActive);
    } else {
        //do shit to send to network
        ClientSocket *sock = determineZone(this);
        if (!sock)
            return;
        QJsonObject jsonPayload;
        jsonPayload["value"] = color;
        jsonPayload["id"] = this->id;
        sock->prepareToSend("RGBW", jsonPayload);
    }
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
        this->statusLabel->setText(text);
    }

    if (this->type == LIGHT_ZWAVE_DIMMABLE)
    {
        text = QString::number(level) + "%";
        this->statusLabel->setText(text);
    }

    if (this->localUpdate)
        sendUpdate();
}

void Light::sendUpdate()
{
    this->statusLabel->setText(QString::number(this->level));
    broadcastMessage(this->id, this->level);
    emit levelChanged(this);
}

// from an active preset - next color
void Light::colorStepAction(QColor color)
{
    setColor(color.name().toUpper().replace("#",""), true);
}

//toggle single rgb(w) strip
void Light::setColorInPWM(QString color, bool keepActive = true)
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
    int r = color.mid(0,2).toInt(&ok, 16);
    int g = color.mid(2,2).toInt(&ok, 16);
    int b = color.mid(4,2).toInt(&ok, 16);
    int w = color.mid(6,2).toInt(&ok, 16);
    qDebug() << color;
    if (this->pwmbank == 0) {
        // devices not on i2c device
        gpioPWM(GPIO_PIN_RED, r);
        gpioPWM(GPIO_PIN_GREEN, g);
        gpioPWM(GPIO_PIN_BLUE, b);
        gpioPWM(GPIO_PIN_WHITE, w);
    } else {
        // well, it's on a fucking i2c bus.
        PCA9685_setDutyCycle(bus, (this->pwmbank - 1) * 4 + 0, r );
        PCA9685_setDutyCycle(bus, (this->pwmbank - 1) * 4 + 1, g );
        PCA9685_setDutyCycle(bus, (this->pwmbank - 1) * 4 + 2, b );
        PCA9685_setDutyCycle(bus, (this->pwmbank - 1) * 4 + 3, w );
    }
}

//read the pwm values for led strip
QString Light::getColorFromPWM()
{
    int r = gpioGetPWMdutycycle(GPIO_PIN_RED);
    int g = gpioGetPWMdutycycle(GPIO_PIN_GREEN);
    int b = gpioGetPWMdutycycle(GPIO_PIN_BLUE);
    int w = gpioGetPWMdutycycle(GPIO_PIN_WHITE);
    return NULL;
}

void Light::setActivePreset(Preset preset)
{
    // a new preset and it's local. kill any tasks
    if (this->isLocal()) {
        if (this->taskList->length() > 0){
            PresetTask *toTerm;
            foreach (toTerm, *this->taskList) {
                toTerm->abortFlag = true;
            }
        }
        this->taskList->clear();
    }

    if (!preset.dynamic)
    {
        if (preset.type == 2){

        } else {
            setColor(preset.getHex());
        }
    } else {
        if (this->isLocal()) {
            PresetTask *task = new PresetTask(&preset);
            this->taskList->append(task);
            task->start();
            connect(task,SIGNAL(colorStepChanged(QColor)), this,SLOT(colorStepAction(QColor)));
            qDebug() << preset.getName();
        } else{
            ClientSocket *sock = determineZone(this);
            if (!sock)
                return;
            QJsonObject jsonPayload;
            jsonPayload["value"] = preset.getID();
            jsonPayload["id"] = this->id;
            sock->prepareToSend("PRESET", jsonPayload);
        }
    }
}

