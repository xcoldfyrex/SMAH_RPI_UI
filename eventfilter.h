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
        if(ev->type() == QEvent::KeyPress || ev->type() == QEvent::MouseButtonRelease || ev->type() == QEvent::TouchEnd)
            emit userActivity(ev);
        return QObject::eventFilter(obj, ev);
    }

signals:
    void userActivity(QEvent *ev);

};

#endif // EVENTFILTER_H
