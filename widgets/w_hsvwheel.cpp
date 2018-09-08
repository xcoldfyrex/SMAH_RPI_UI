#include <QScreen>
#include <QMatrix>
#include <QtCore/qmath.h>

#include "w_hsvpalette.h"

HSVWheel::HSVWheel(QWidget *parent) :
    QWidget(parent),
    initSize(700,200),
    mouseDown(false),
    margin(0),
    wheelWidth(120),
    current(Qt::red),
    inWheel(false),
    inSquare(false)
{
    current = current.toHsv();
    setCursor(Qt::CrossCursor);
}

QColor HSVWheel::color()
{
    return current;
}

void HSVWheel::setColor(const QColor &color)
{
    if(color == current) return;
    if(color.hue() != current.hue()){
        colorChanged(color.hue());
    }
    update();
    emit colorChange(color);
}


QSize HSVWheel::sizeHint () const
{
    return QSize(height(),height());
}

QSize HSVWheel::minimumSizeHint () const
{
    return initSize;
}

void HSVWheel::mousePressEvent(QMouseEvent *event)
{
    QPixmap pm = this->grab();
    if (((event->x() < 0) || (event->x() > pm.width())) || ((event->y() < 0) || event->y() > pm.height())) return;
    QColor color = pm.toImage().pixel(event->x(),event->y());
    colorChanged(color);
    mouseDown = true;
}

void HSVWheel::mouseMoveEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if( !mouseDown ) return;
    QPixmap pm = this->grab();
    if (((event->x() < 0) || (event->x() > pm.width())) || ((event->y() < 0) || event->y() > pm.height())) return;
    QColor color = pm.toImage().pixel(event->x(),event->y());
    colorChanged(color);
}

void HSVWheel::mouseReleaseEvent(QMouseEvent *)
{
    mouseDown = false;
    inWheel = false;
    inSquare = false;
}

void HSVWheel::resizeEvent(QResizeEvent *event)
{
    wheel = QPixmap(event->size());
    drawPalette(event->size());
    update();
}

void HSVWheel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.initFrom(this);
    composePalette();
    painter.drawPixmap(0,0,wheel);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void HSVWheel::drawPalette(const QSize &newSize)
{
    QStyleOption option;
    option.initFrom(this);
    QBrush background = option.palette.window();
    wheelImage = QImage(newSize, QImage::Format_ARGB32_Premultiplied);
    wheelImage.fill(background.color());
    QPainter painter(&wheelImage);
    float step = ((float) this->width() / (float) 360);
    float offset = 1;

    for(int h = 0; h <= 360; ++h)
    {
        QColor colorHSV;
        colorHSV.setHsv(h,255,255);
        QLinearGradient gradient(QPointF(0,0), QPointF(0, this->height()));
        gradient.setColorAt(1.0, Qt::white);
        gradient.setColorAt(0.5, colorHSV);
        gradient.setColorAt(0.0, Qt::black);
        QBrush brush(gradient);
        QPen paintpen;
        paintpen.setBrush(brush);
        painter.setPen(paintpen);
        for (float x = 0; x <= step; x++) {

            painter.drawLine(offset + step + x, 0, offset + step + x, this->height());
        }
        offset = offset + step;
    }
}

void HSVWheel::composePalette()
{
    QPainter composePainter(&wheel);

    QColor color;
    color.setBlue(255);
    QPen paintpen(color);
    composePainter.setPen(paintpen);
    QBrush brush2;
    brush2.setColor(color);
    brush2.setStyle(Qt::SolidPattern);
    composePainter.setBrush(brush2);
    composePainter.drawRect(0, 0, 600, 600);
    composePainter.drawImage(0, 0, wheelImage);
}

void HSVWheel::colorChanged(QColor color)
{
    if(!isVisible()) return;
    emit colorChange(color);
}
