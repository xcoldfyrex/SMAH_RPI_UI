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

#include "w_colorpreview.h"
#include "light.h"
#include "zone.h"


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
    QHBoxLayout *contentLayout;
    QPicture *hsvSwatch;
    QColor rgb;
    QPushButton *btnSelectPreset;
    QListWidget *zoneButtons;

public slots:
    void updateFromWheel(QColor qcol);

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
    Zone zone;
    Light *light;
};

#endif // LIGHTCONTROLWIDGET_H
