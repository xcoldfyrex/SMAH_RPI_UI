#include <QMetaEnum>
#include "scheduled_actions.h"

ScheduledActions::ScheduledActions() {}

void ScheduledActions::add_action(QString action, QVariant val, QString time)
{
    QTime parsedTime = QTime::fromString(time);
    QMetaEnum metaEnum = QMetaEnum::fromType<Action>();

    bool ok;
    Action value = static_cast<Action>(metaEnum.keyToValue(action.toStdString().c_str(), &ok));
    if (!ok) {
        // Handle error: the string did not match any enum key
        qWarning() << "Failed matching enum type of" << action;
    }

    mFunctions tempValues;
    tempValues.action = value;
    tempValues.val = val;
    tempValues.time = parsedTime;
    mActionList.append(tempValues);
}
