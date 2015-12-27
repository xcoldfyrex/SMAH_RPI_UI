#ifndef LIGHTCONTROLWIDGET_H
#define LIGHTCONTROLWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QPicture>
#include "w_colorpreview.h"


namespace Ui {
class LightControlWidget;
}

class LightControlContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightControlContainerWidget(QWidget *parent = 0);
    ~LightControlContainerWidget();
    QWidget *topWidget;
    QWidget *colorPalette;
    ColorPreview *preview;
    QGridLayout *contentLayout;
    QPicture *hsvSwatch;
    QColor rgb;

public slots:
    void updateHSVSelected(QColor qcol);
    void updateBrightnessSelected(QColor qcol);

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
};

#endif // LIGHTCONTROLWIDGET_H
