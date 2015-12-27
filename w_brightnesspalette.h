#ifndef BRIGHTNESSPALETTE_H
#define BRIGHTNESSPALETTE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPen>
#include <QMouseEvent>

class BrightnessPalette : public QWidget
{
    Q_OBJECT
public:
    explicit BrightnessPalette(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    void mouseMoveEvent(QMouseEvent *event);
    QPainter painter;

signals:
    void changed(QColor hsv);

public slots:
};

#endif // BRIGHTNESSPALETTE_H
