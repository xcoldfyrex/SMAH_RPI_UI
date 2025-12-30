#include <QMetaEnum>
#include "scheduled_actions.h"
#include "shelly.h"

extern QMap <QString, Shelly*> g_shellyList;

ScheduledActions::ScheduledActions() {}

void ScheduledActions::add_action(QDomElement data)
{
    QDomNodeList actionItems = data.elementsByTagName("action");
    QList<ScheduledActions> actions;
    for (int a = 0; a < actionItems.count(); a++) {
        QDomNode actionNode = actionItems.at(a);
        if (actionNode.isElement()) {
            QDomElement element = actionNode.toElement();
            QString tempaction = element.attribute("action");
            QString device = element.attribute("device");

            // determine if the time is fixed or an offest
            QTime parsedTime;
            QString timeAttribute = element.attribute("time");
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

            QMetaEnum metaEnum = QMetaEnum::fromType<Action>();
            bool ok;
            Action action = static_cast<Action>(metaEnum.keyToValue(tempaction.toStdString().c_str(), &ok));
            if (!ok) {
                // Handle error: the string did not match any enum key
                qWarning() << "Failed matching enum type of" << action;
            }
            mFunctions *tempValues = new mFunctions();

            if (g_shellyList.contains(device))
            {
                tempValues->device = g_shellyList.value(device);
            } else {
                qWarning() << "Action" << action << "references device that was not found:" << device;
                return;
            }

            tempValues->action = action;
            tempValues->val = element.attribute("value");
            tempValues->interval = element.attribute("interval").toInt();
            tempValues->repeats = element.attribute("repeat").toInt();
            tempValues->remaining = tempValues->repeats;
            tempValues->time = parsedTime;
            mActionList.append(tempValues);

            //QTimer *timer = new QTimer(this);
            connect(tempValues->timer, &QTimer::timeout, this, [tempValues]() {
                QString strType;
                switch (tempValues->action) {
                case Action::SHELLY_ON:
                    strType = "on";
                    break;
                case Action::SHELLY_BRIGHTNESS:
                    strType = "brightness";
                    break;
                case Action::SHELLY_RGB:
                    strType = "rgb";
                    break;
                case Action::SHELLY_WHITE:
                    strType = "white";
                    break;
                case Action::SHELLY_TRANSITION_DURATION:
                    strType = "transition_duration";
                    break;
                case Action::SHELLY_TOGGLE_AFTER:
                    strType = "toggle_after";
                    break;
                case Action::SHELLY_OFFSET:
                    strType = "offset";
                    break;
                case Action::SHELLY_OFFSET_WHITE:
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
                if (strType == "rgb") {
                    tempValues->device->setRGBW(tempValues->val.toString());
                } else {
                    tempValues->device->setValue(strType,tempValues->val.toString(),tempValues->on);
                }

                qDebug() << tempValues->time << tempValues->interval << tempValues->remaining << tempValues->repeats << tempValues->interval << tempValues->timer->remainingTime();
            });

            //calculate when the first run should be
            int delay = QTime::currentTime().secsTo(parsedTime);
            if (delay < 0 )
                delay += 86400;
            tempValues->timer->start(delay * 1000);
        }
    }

}

void ScheduledActions::checkTime(mFunctions mFunction)
{
    QTime now = QTime::currentTime();
    //QTime targetTime(QTime(now.), QTime(15, 0, 0)); // Set target time
    qDebug() << mFunction.time;
}
