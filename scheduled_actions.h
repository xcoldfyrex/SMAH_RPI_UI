#ifndef SCHEDULED_ACTIONS_H
#define SCHEDULED_ACTIONS_H

#include "shelly.h"
#include <QObject>
#include <QDateTime>
#include <QDomElement>
#include <QTimer>


class ScheduledActions : public QObject
{
    Q_OBJECT

public:

    enum class Action {
        SHELLY_ON,
        SHELLY_BRIGHTNESS,
        SHELLY_RGB,
        SHELLY_WHITE,
        SHELLY_TRANSITION_DURATION,
        SHELLY_TOGGLE_AFTER,
        SHELLY_OFFSET,
        SHELLY_OFFSET_WHITE
    };

    enum class ActionType {
        SHELLY_RGBW,
    };

    Q_ENUM(Action);
    Q_ENUM(ActionType);

    ScheduledActions();
    void add_action(QDomElement data);

private:
    struct mFunctions
    {
        ScheduledActions::Action action;
        ScheduledActions::ActionType actionType;
        QVariant val;
        // start time
        QTime time;
        int repeats = 0;
        // interval in seconds in which to repeat
        int interval = 0;
        // TODO: remove this hardcode so we can have other devices
        Shelly *device;
        bool on = true;
        bool isRunning = false;
        int remaining = 0;
        QTimer *timer = new QTimer();
    };

    struct mFunctionStatus
    {
        bool isRunning = false;
        int remaining = 0;
    };

    QList<mFunctions*> mActionList;

public slots:
    void checkTime(mFunctions mFunction);

};

#endif // SCHEDULED_ACTIONS_H
