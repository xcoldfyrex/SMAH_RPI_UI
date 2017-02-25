#include "w_hslswatch.h"

HSLSwatch::HSLSwatch(QWidget *parent) : QWidget(parent)
{
    current = current.toHsv();
}

void HSLSwatch::drawSquareImage(const int &hue)
{
    QImage square(255,255, QImage::Format_ARGB32_Premultiplied);
    QColor color;
    QRgb vv;
    for(int i=0;i<255;++i){
        for(int j=0;j<255;++j){
            color = QColor::fromHsv(hue,i,j);
            vv = qRgb(color.red(),color.green(),color.blue());
            square.setPixel(i,j,vv);
        }
    }
    // qreal SquareWidth = 2*ir/qSqrt(2);
    squareImage = square.scaled(width(),height());
    //    painter.drawImage(0,0,square);

    //    QPainter painter2(&wheel);
    //    painter2.drawImage(0,0,source);

    squareRegion = QRegion(0, 0, width(),height());
}

void HSLSwatch::compose()
{
    QPainter composePainter(&square);

    QColor color;
    color.setBlue(255);
    QPen paintpen(color);
    composePainter.setPen(paintpen);
    QBrush brush2;
    brush2.setColor(color);
    brush2.setStyle(Qt::SolidPattern);
    composePainter.setBrush(brush2);
    composePainter.drawRect(0, 0, 600, 600);

    //return;
    composePainter.drawImage(0, 0, squareImage);
    //    composePainter.drawImage(wheelImage.width() +1, 0, squareImage);
    //composePainter.drawImage(squareRegion.boundingRect().topLeft(), squareImage);
    composePainter.end();
    //drawIndicator(current.hue());
    //drawPicker(current);
}


QColor HSLSwatch::posColor(const QPoint &point)
{
    if( ! square.rect().contains(point) ) return QColor();

    // region of the widget
    int w = qMin(width(), height());
    QRgb pixel = squareImage.pixel(point.x(), point.y());
    return QColor(pixel);
}

void HSLSwatch::resizeEvent(QResizeEvent *event)
{

    square = QPixmap(event->size());
    drawSquareImage(current.hue());
    update();
}

void HSLSwatch::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    compose();
    painter.drawPixmap(0,0,square);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void HSLSwatch::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    QColor color = posColor(lastPos);
    emit colorChange(color);
    mouseDown = true;
}

void HSLSwatch::mouseMoveEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if( !mouseDown ) return;
    QColor color = posColor(lastPos);
    emit colorChange(color);
}

void HSLSwatch::mouseReleaseEvent(QMouseEvent *)
{
    mouseDown = false;
}

void HSLSwatch::updateHue(QColor color)
{
    current.setHsv(color.hue(), current.saturation(), current.value());
    compose();
    repaint();
    update();

}
