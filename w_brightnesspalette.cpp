#include "w_brightnesspalette.h"

BrightnessPalette::BrightnessPalette(QWidget *parent) : QWidget(parent)
{

}

void BrightnessPalette::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    float step = ((float) this->width() / (float) 255);
    float offset = 0;

    for(int h = 0; h <= 255; ++h)
    {
        QColor colorBW;
        colorBW.setRgb(h,h,h);
        QPen paintpen(colorBW);
        painter.setPen(paintpen);
        for (float x = 0; x <= step; x++) {
            painter.drawLine(offset + step + x, 0, offset + step + x, this->height());
        }
        offset = offset + step;
    }
}

void BrightnessPalette::mouseMoveEvent(QMouseEvent *event)
{
    QPixmap pm = this->grab();
    if (((event->x() < 0) || (event->x() > pm.width())) || ((event->y() < 0) || event->y() > pm.height())) return;
    QColor color = pm.toImage().pixel(event->x(),event->y());
    emit changed(color);
}
