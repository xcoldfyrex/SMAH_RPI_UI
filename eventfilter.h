#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include <QEvent>
#include <QDebug>

class EventFilter : public QObject
{
    Q_OBJECT
protected:
    bool eventFilter(QObject *obj, QEvent *ev)
    {
        if(ev->type() == QEvent::KeyPress || ev->type() == QEvent::MouseButtonPress)
            emit userActivity();
        return QObject::eventFilter(obj, ev);
    }

signals:
    void userActivity();

};

#endif // EVENTFILTER_H
