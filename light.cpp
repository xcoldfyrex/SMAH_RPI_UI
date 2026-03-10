#include <QDebug>
#include <QTimer>
#include "qapplication.h"

#include "light.h"
#include "shelly.h"

//Q_DECLARE_METATYPE(Light)

Light::Light(QObject *parent) : QObject(parent)
{
}

Light::Light(QString name, Shelly *shellydevice)
{
    // TODO: rework tis so it's not blocking
    this->name = name;
    this->shellydevice = shellydevice;

    while (this->shellydevice->getApp() == "" && (!this->shellydevice->isReady()))
    {
        QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qInfo() << this->shellydevice->getID() << this->name << "slow to respond, polling..";

    }

    if (this->shellydevice->getApp() != "") {
        this->type = shellydevice->getApp();

        this->taskList = new QList<PresetTask*>();
        QObject::connect(shellydevice, &Shelly::messageRecv, this, &Light::shellyUpdated);
    }
}

    /*
     *     QTimer *polltimer = new QTimer(this);
    polltimer->setInterval(1000);
    polltimer->start();
    connect(polltimer, &QTimer::timeout, this, [this, shellydevice, polltimer]() {
    while (this->shellydevice->getApp() == "" && (!this->shellydevice->isReady()))
    {
        QTime dieTime = QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime) {
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qInfo() << this->shellydevice->getID() << this->name << "slow to respond, polling..";
        if (this->shellydevice->getApp() != "") {
            this->type = shellydevice->getApp();

            this->taskList = new QList<PresetTask*>();
            QObject::connect(shellydevice, &Shelly::messageRecv, this, &Light::shellyUpdated);
            polltimer->stop();
            polltimer->deleteLater();
        }
    }
    });
     * /

}


/* flip the power state of a light */
void Light::toggleState()
{
    if (this->getState()) {
        this->setState(0);
    } else {
        this->setState(1);
    }
    emit stateChanged();
    return;
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
