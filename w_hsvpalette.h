#ifndef HSVPALETTE_H
#define HSVPALETTE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPen>
#include <QMouseEvent>

class HSVWheel : public QWidget
{
    Q_OBJECT
public:
    explicit HSVWheel(QWidget *parent = 0);

    virtual QSize sizeHint () const;
    virtual QSize minimumSizeHint () const;
    QColor color();

signals:
    void colorChange(const QColor &color);

public slots:
    void setColor(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
private:
    QSize initSize;
    QImage wheelImage;
    QPixmap wheel;
    bool mouseDown;
    QPoint lastPos;
    int margin;
    int wheelWidth;
    QRegion wheelRegion;
    QColor current;
    bool inWheel;
    bool inSquare;
    QColor posColor(const QPoint &point);
    void drawWheelImage(const QSize &newSize);
    void drawIndicator(const int &hue);
    void drawPicker(const QColor &color);
    void composeWheel();
private slots:
    void hueChanged(const int &hue);
};

#endif // HSVPALETTE_H
