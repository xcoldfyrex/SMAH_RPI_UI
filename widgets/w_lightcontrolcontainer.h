#ifndef LIGHTCONTROLWIDGET_H
#define LIGHTCONTROLWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QPicture>
#include <QListWidgetItem>
#include <QPushButton>

#include "w_hslswatch.h"
#include "w_colorpreview.h"
#include "light.h"
#include "zone2.h"


namespace Ui {
class LightControlWidget;
}

class LightControlContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightControlContainerWidget(Zone zone, Light *light, QWidget *parent = 0);
    LightControlContainerWidget() {}
    ~LightControlContainerWidget();
    QWidget *topWidget;
    QWidget *colorPalette;
    ColorPreview *preview;
    QGridLayout *contentLayout;
    QPicture *hsvSwatch;
    QColor rgb;
    QPushButton *btnShowPreset;

public slots:
    void updateFromWheel(QColor qcol);
    void updateFromSwatch(QColor qcol);

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
    HSLSwatch *hslSwatch;
    Zone zone;
    Light *light;
};

#endif // LIGHTCONTROLWIDGET_H
