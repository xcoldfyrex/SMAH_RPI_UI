#include "w_colorpreview.h"

ColorPreview::ColorPreview(QWidget *parent) : QWidget(parent)
{

}

void ColorPreview::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen paintpen(color);
    QPen penHText(QColor("#CCCCCC"));
    QBrush brush;
    QFont font=painter.font() ;

    color.setRgb(color.red(),color.green(),color.blue());
    painter.setPen(paintpen);
    font.setPointSize(18);
    painter.setFont(font);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.drawRect(0, 40, this->width()-1, 100);
    painter.setPen(penHText);
    painter.drawText(0,20, color.name().replace("#",""));
}
