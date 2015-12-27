#ifndef ZONECONTAINERWIDGET_H
#define ZONECONTAINERWIDGET_H

#endif // ZONECONTAINERWIDGET_H

#include <QWidget>

class ZoneContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneContainerWidget(QWidget *parent = 0);
    QWidget *topWidget;

private:
};
