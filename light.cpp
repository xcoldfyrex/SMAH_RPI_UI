#include "light.h"
#include "qapplication.h"
#include "shelly.h"

extern QString MY_HW_ADDR;
extern int MY_DEVICE_ID;

//Q_DECLARE_METATYPE(Light)

Light::Light(QObject *parent) : QObject(parent)
{
}

Light::Light(int id, QString name, Shelly *shellydevice)
{
    this->id = id;
    this->name = name;
    this->shellydevice = shellydevice;
    while (this->shellydevice->getApp() == "" && (!this->shellydevice->isReady()))
    {
        QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() << this->name << "slow to respond, polling..";

    }
    this->type = shellydevice->getApp();
    //this->state = shellydevice.
    //qDebug() << this->type << this->name;

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
    shellydevice->setRGBW(r,g,b,w);
}

void Light::setActivePreset(Preset *preset)
{
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

void Light::setStateShelly(bool state) {
    shellydevice->setState(state);
}

void Light::setBrightnessShelly(int brightness) {
    shellydevice->setBrightness(brightness);
}
