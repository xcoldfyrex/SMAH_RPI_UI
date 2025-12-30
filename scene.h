#ifndef SCENE_H
#define SCENE_H

#include <QObject>

#include "shelly.h"

class Scene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant name READ getName NOTIFY modified())

public:
    Scene();
    Scene(QString name);
    Q_INVOKABLE

    Q_INVOKABLE void activate();
    Q_INVOKABLE void addItem(Shelly *shelly, QVariant val, bool state);

    QString getName() { return this->name; }


private:
    QString name = "undef";

    struct mFunctions
    {
        QVariant val;
        bool state = 0;
        // TODO: remove this hardcode so we can have other devices
        Shelly *device;
    };

    QList<mFunctions> mItemList;

signals:
    void activated();
    void modified();
};

#endif // SCENE_H
