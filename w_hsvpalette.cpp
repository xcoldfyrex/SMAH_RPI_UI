#include "w_hsvpalette.h"
#include <QDebug>
#include <QScreen>

HSVPalette::HSVPalette(QWidget *parent) : QWidget(parent)
{


}

void HSVPalette::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    float step = ((float) this->width() / (float) 360);
    float offset = 1;

    for(int h = 0; h <= 360; ++h)
    {
        QColor colorHSV;
        colorHSV.setHsv(h,255,255);
        QPen paintpen(colorHSV);
        painter.setPen(paintpen);
        for (float x = 0; x <= step; x++) {
            painter.drawLine(offset + step + x, 0, offset + step + x, this->height());
        }
        offset = offset + step;
    }
    qDebug() << step;
}


void HSVPalette::mouseMoveEvent(QMouseEvent *event)
{
    QPixmap pm = this->grab();
    if (((event->x() < 0) || (event->x() > pm.width())) || ((event->y() < 0) || event->y() > pm.height())) return;
    QColor color = pm.toImage().pixel(event->x(),event->y());
    //qDebug() << color << event->x() << event->y() << pm.size();
    emit changed(color);
}
