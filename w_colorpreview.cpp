#include <QDebug>

#include "w_colorpreview.h"

ColorPreview::ColorPreview(QWidget *parent) : QWidget(parent)
{

}

void ColorPreview::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED(pe);
    QPainter painter(this);
    color.setRgb(color.red(),color.green(),color.blue());
    QPen paintpen(color);
    painter.setPen(paintpen);
    QBrush brush;
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(0, 0, this->width()-1, this->height());
}
