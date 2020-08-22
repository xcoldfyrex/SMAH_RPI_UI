#include "light.h"
#include "pigpio.h"
#include "gpio_defs.h"
#include "commandrouter.h"
#include "tcpconnectionfactory.h"
#include "pca9685.h"

#include <QDebug>

extern QMap <QString, RPIDevice> g_deviceList;
extern QString MY_HW_ADDR;
extern int MY_DEVICE_ID;
extern I2C bus;
extern TCPConnectionFactory tcpServer;

//Q_DECLARE_METATYPE(Light)

Light::Light(QObject *parent) : QObject(parent)
{
    this->statusLabel = new QLabel("N/A");
}

Light::Light(int id, QString name, int type, int deviceid, short bank, uint32 home_id)
{
    this->id = id;
    this->name = name;
    this->type = type;
    this->statusLabel = new QLabel("N/A");
    this->deviceid = deviceid;
    this->taskList = new QList<PresetTask*>();
    this->pwmbank = bank;
    this->home_id = home_id;
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
        QJsonObject jsonPayload;
        jsonPayload["id"] = this->id;
        //ClientSocket *sock = determineZone(this);
        //if (!sock) {
        // pray and broadcast. need to send to proper home_id
        jsonPayload["home_id"] = (int) this->home_id;
        tcpServer.broadcastMessageJSON("TOGGLE", jsonPayload);
        return;
        //}
        //sock->prepareToSend("TOGGLE", jsonPayload);
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
        text = QString::number(level) + '%';
        this->statusLabel->setText(text);
    }

    if (this->localUpdate)
        sendUpdate();
}

void Light::setLevel(int level)
{
    if (this->type == LIGHT_ZWAVE_DIMMABLE)
    {
        if (this->isLocal())
        {
            //this->level = level;
            setZWaveLevel(level, this->id);
        } else {
            QJsonObject jsonPayload;
            jsonPayload["id"] = this->id;
            //ClientSocket *sock = determineZone(this);
            //if (!sock) {
            // pray and broadcast. need to send to proper home_id
            jsonPayload["home_id"] = (int) this->home_id;
            jsonPayload["value"] = level;
            tcpServer.broadcastMessageJSON("LEVEL", jsonPayload);
            return;
            //}
        }
        //sock->prepareToSend("LEVEL", jsonPayload);
    }
}

void Light::sendUpdate()
{
    this->statusLabel->setText(QString::number(this->level));
    tcpServer.broadcastMessage(this->id, 0, this->level, 0);
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
    short r = color.mid(0,2).toShort(&ok, 16);
    short g = color.mid(2,2).toShort(&ok, 16);
    short b = color.mid(4,2).toShort(&ok, 16);
    short w = color.mid(6,2).toShort(&ok, 16);
    if (this->pwmbank == 0) {
        // devices not on i2c device
        gpioPWM(GPIO_PIN_RED, static_cast<uint>(r));
        gpioPWM(GPIO_PIN_GREEN, static_cast<uint>(g));
        gpioPWM(GPIO_PIN_BLUE, static_cast<uint>(b));
        gpioPWM(GPIO_PIN_WHITE, static_cast<uint>(w));
    } else {
        // well, it's on a fucking i2c bus.
        // also matt is a fucking wanker and sj is a troglodite
        PCA9685 pca(1, 0x40);
        pca.setPWMFreq(1000);
        pca.setPWM((this->pwmbank - 1) * 4 + 1, r * 10);
        pca.setPWM((this->pwmbank - 1) * 4 + 2, g * 10);
        pca.setPWM((this->pwmbank - 1) * 4 + 3, b * 10);
        pca.setPWM((this->pwmbank - 1) * 4 + 4, w * 10);
    }
}

//read the pwm values for led strip
QList<int> Light::getColorFromPWM()
{
    QList<int> vals;
    vals.append(gpioGetPWMdutycycle(GPIO_PIN_RED));
    vals.append(gpioGetPWMdutycycle(GPIO_PIN_GREEN));
    vals.append(gpioGetPWMdutycycle(GPIO_PIN_BLUE));
    vals.append(gpioGetPWMdutycycle(GPIO_PIN_WHITE));
    return vals;
}

void Light::setActivePreset(Preset *preset)
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

    if (!preset->dynamic)
    {
        if (preset->type == 2){

        } else {
            setColor(preset->getHex());
        }
    } else {
        if (this->isLocal()) {
            PresetTask *task = new PresetTask(preset);
            this->taskList->append(task);
            task->start();
            connect(task,SIGNAL(colorStepChanged(QColor)), this,SLOT(colorStepAction(QColor)));
            qDebug() << preset->getName();
        } else{
            ClientSocket *sock = determineZone(this);
            if (!sock)
                return;
            QJsonObject jsonPayload;
            jsonPayload["value"] = preset->getID();
            jsonPayload["id"] = this->id;
            sock->prepareToSend("PRESET", jsonPayload);
        }
    }
}

