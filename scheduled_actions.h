#ifndef SCHEDULED_ACTIONS_H
#define SCHEDULED_ACTIONS_H

#include "shelly.h"
#include "configuration.h"
#include <QObject>
#include <QDateTime>
#include <QDomElement>
#include <QTimer>

class ScheduledActionsItem  : public QObject
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
    // is this actually used?
    enum class ActionType {
        SHELLY_RGBW,
    };

    Q_ENUM(Action);
    Q_ENUM(ActionType);

    ScheduledActionsItem();
    Action action = Action::SHELLY_ON;
    ActionType actionType = ActionType::SHELLY_RGBW;
    QVariant val = 0;
    // start time
    QTime time = QTime::fromString("00:00");
    int repeats = 0;
    // interval in seconds in which to repeat
    int interval = 0;
    bool on = true;
    bool isRunning = false;
    int remaining = 0;
    QTimer *timer = new QTimer();

    QVariant getVal() { return this->val ;};
    QVariant getTime() { return this->time ;};


    Q_PROPERTY(QVariant time READ getVal CONSTANT);

    Q_PROPERTY(QVariant val READ getVal CONSTANT);
};

class ScheduledActions : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString name READ getName CONSTANT);

    ScheduledActions(QString mName);
    void add_action(Configuration::ActionItemConfiguration data);

    QString getName() { return this->name; };
    QList<Shelly*> getDevices() { return this->shellyDevices; };
    void addShelly(Shelly* shelly);
    void removeShelly(Shelly* shelly);


private:
    struct mFunctionStatus
    {
        bool isRunning = false;
        int remaining = 0;
    };

    QList<ScheduledActionsItem*> mActionList;
    QList<Shelly*> shellyDevices;
    QString name;

public slots:
    //void checkTime(ScheduledActionsItem mFunction);

public:
    Q_INVOKABLE QList<ScheduledActionsItem*> getActionList() { return this->mActionList; };

};



#endif // SCHEDULED_ACTIONS_H
