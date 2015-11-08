#include "hsvpalette.h"
#include <QDebug>
#include <QScreen>

HSVPalette::HSVPalette(QWidget *parent) : QWidget(parent)
{


}

void HSVPalette::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    for(int h = 0; h <= 360; ++h)
        {
           QColor colorHSV;
           colorHSV.setHsv(h,255,255);
           //QColor colorHSV = colorRGB.toHsv();
           QPen paintpen(colorHSV);
           painter.setPen(paintpen);
           //painter.setBrush(paintpen);
           painter.drawLine(h,0,h,100);

    }
}

void HSVPalette::mouseMoveEvent(QMouseEvent *event)
{

 QPixmap pm = this->grab();
 //pm = QScreen::grabWindow(this->winId(), QCursor::pos().x(), QCursor::pos().y(), 1, 1);
 QColor color = pm.toImage().pixel(QCursor::pos().x(),QCursor::pos().y());


qDebug() << color << QCursor::pos().x() << QCursor::pos().y() << pm.size();
         //state = 1;
         repaint();
         emit changed();

}
