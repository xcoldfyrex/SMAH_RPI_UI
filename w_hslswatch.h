#ifndef HSLSWATCH_H
#define HSLSWATCH_H


#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOption>


class HSLSwatch : public QWidget
{
    Q_OBJECT

public:
    explicit HSLSwatch(QWidget *parent = 0);

public slots:
    void updateHue(QColor color);

signals:
    void colorChange(QColor color);

private:
    void drawSquareImage(const int &hue);
    void compose();
    QImage squareImage;
    QRegion squareRegion;
    QColor current;
    QPixmap square;
    QPoint lastPos;
    bool mouseDown;
    QColor posColor(const QPoint &point);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
};

#endif // HSLSWATCH_H
