#ifndef SCHEDULEDACTIONS_H
#define SCHEDULEDACTIONS_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class ScheduledActionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduledActionsWidget(QWidget *parent = 0);
    QWidget *topWidget;
    QListWidget *actiontList;
    QVBoxLayout *contentLayout;
signals:

public slots:
};

#endif // SCHEDULEDACTIONS_H
