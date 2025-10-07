#ifndef SCHEDULED_ACTIONS_H
#define SCHEDULED_ACTIONS_H

#include <QObject>
#include <QDateTime>


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
    void add_action(QString action, QVariant val, QString time);

private:

    struct mFunctions
    {
        ScheduledActions::Action action;
        ScheduledActions::ActionType actionType;
        QVariant val;
        QTime time;
        int repeats = 0;
    };

    QList<mFunctions> mActionList;
};

#endif // SCHEDULED_ACTIONS_H
