#include <QMetaEnum>
#include "scheduled_actions.h"
#include "shelly.h"

ScheduledActionsItem::ScheduledActionsItem() {

}

ScheduledActions::ScheduledActions(QString mName) {
    this->name = mName;
}

void ScheduledActions::add_action(Configuration::ActionItemConfiguration data)
{
    QString tempaction = data.mAction;

    // determine if the time is fixed or an offest
    QTime parsedTime;
    QString timeAttribute = data.mTime;
    if (timeAttribute.startsWith("+")) {
        //verify we are not at the state of the actions list, otherwise problems
        if (mActionList.length() == 0) {
            qWarning() << "Action defines an offset, but is first in series";
            return;
        }
        parsedTime = mActionList.at(mActionList.length() -1)->time;
        parsedTime = parsedTime.addSecs(timeAttribute.replace("+","").toInt() * 60 );
    } else {
        parsedTime = QTime::fromString(timeAttribute);
    }

    QMetaEnum metaEnum = QMetaEnum::fromType<ScheduledActionsItem::Action>();
    bool ok;
    ScheduledActionsItem::Action action = static_cast<ScheduledActionsItem::Action>(metaEnum.keyToValue(tempaction.toStdString().c_str(), &ok));
    if (!ok) {
        // Handle error: the string did not match any enum key
        qWarning() << "Failed matching enum type of" << action;
    }

    ScheduledActionsItem *tempValues = new ScheduledActionsItem();
    /*
            if (g_shellyList.contains(device))
            {
                tempValues->device = g_shellyList.value(device);
            } else {
                qWarning() << "Action" << action << "references device that was not found:" << device;
                return;
            }
*/
    tempValues->action = action;
    tempValues->val = data.mValue;
    tempValues->interval = data.mInterval;
    tempValues->repeats = data.mRepeat;
    tempValues->remaining = tempValues->repeats;
    tempValues->time = parsedTime;
    mActionList.append(tempValues);

    //QTimer *timer = new QTimer(this);
    connect(tempValues->timer, &QTimer::timeout, this, [tempValues, this]() {
        QString strType;
        switch (tempValues->action) {
        case ScheduledActionsItem::Action::SHELLY_ON:
            strType = "on";
            break;
        case ScheduledActionsItem::Action::SHELLY_BRIGHTNESS:
            strType = "brightness";
            break;
        case ScheduledActionsItem::Action::SHELLY_RGB:
            strType = "rgb";
            break;
        case ScheduledActionsItem::Action::SHELLY_WHITE:
            strType = "white";
            break;
        case ScheduledActionsItem::Action::SHELLY_TRANSITION_DURATION:
            strType = "transition_duration";
            break;
        case ScheduledActionsItem::Action::SHELLY_TOGGLE_AFTER:
            strType = "toggle_after";
            break;
        case ScheduledActionsItem::Action::SHELLY_OFFSET:
            strType = "offset";
            break;
        case ScheduledActionsItem::Action::SHELLY_OFFSET_WHITE:
            strType = "offset_white";
            break;
        default:
            break;
        }
        qDebug() << tempValues->time << tempValues->interval << tempValues->remaining << tempValues->repeats;

        // reset the main timer
        if (tempValues->repeats > 0 && tempValues->remaining > 0) {
            tempValues->timer->start(tempValues->interval * 1000);
            tempValues->remaining--;
        } else {
            tempValues->remaining = tempValues->repeats;
            int delay = QTime::currentTime().secsTo(tempValues->time);
            if (delay < 1 )
                delay += 86400;
            tempValues->timer->start(delay * 1000);
        }
        // now set the state of each device associated with the action
        for (Shelly *device : this->shellyDevices) {
            if (strType == "rgb") {
                device->setRGBW(tempValues->val.toString());
            } else {
                device->setValue(strType,tempValues->val.toString(),tempValues->on);
            }
            device = nullptr;
        }
        qDebug() << tempValues->time << tempValues->interval << tempValues->remaining << tempValues->repeats << tempValues->interval << tempValues->timer->remainingTime();
    });

    //calculate when the first run should be
    int delay = QTime::currentTime().secsTo(parsedTime);
    if (delay < 0 )
        delay += 86400;
    tempValues->timer->start(delay * 1000);
    // }
    //}

}
/*

void ScheduledActions::checkTime(ScheduledActionsItem mFunction)
{
    QTime now = QTime::currentTime();
    //QTime targetTime(QTime(now.), QTime(15, 0, 0)); // Set target time
    qDebug() << mFunction.time;
}
*/
void ScheduledActions::addShelly(Shelly* shelly) {
    if (! this->shellyDevices.contains(shelly))
        this->shellyDevices.append(shelly);
}

void ScheduledActions::removeShelly(Shelly* shelly) {
    if (this->shellyDevices.contains(shelly))
        this->shellyDevices.append(shelly);
}
