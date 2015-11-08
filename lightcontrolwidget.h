#ifndef LIGHTCONTROLWIDGET_H
#define LIGHTCONTROLWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QPicture>


namespace Ui {
class LightControlWidget;
}

class LightControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightControlWidget(QWidget *parent = 0);
    ~LightControlWidget();
    QWidget *topWidget;
    QWidget *colorPalette;
    void paintEvent(QPaintEvent *pe);
    QGridLayout *contentLayout;
    QPicture *hsvSwatch;

public slots:
    void updateHSVSelected();

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
};

#endif // LIGHTCONTROLWIDGET_H
