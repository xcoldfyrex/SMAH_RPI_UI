#ifndef COLORPREVIEW_H
#define COLORPREVIEW_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class ColorPreview : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPreview(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    QColor color;

signals:

public slots:
};

#endif // COLORPREVIEW_H
