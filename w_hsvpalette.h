#ifndef HSVPALETTE_H
#define HSVPALETTE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPen>
#include <QMouseEvent>

class HSVPalette : public QWidget
{
    Q_OBJECT
public:
    explicit HSVPalette(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    void mouseMoveEvent(QMouseEvent *event);
    QPainter painter;

signals:
    void changed(QColor hsv);

public slots:
};

#endif // HSVPALETTE_H
