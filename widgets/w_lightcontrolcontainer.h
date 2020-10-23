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
#include <QCheckBox>

#include "w_colorpreview.h"
#include "light.h"
#include "zone.h"

/*
namespace Ui {
class LightControlWidget;
}

class LightControlContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightControlContainerWidget(Zone *zone, Light *light, QWidget *parent = nullptr);
    LightControlContainerWidget() {}
    ~LightControlContainerWidget();
    QWidget *topWidget;
    QWidget *colorPalette;
    ColorPreview *preview;
    QHBoxLayout *contentLayout;
    QPicture *hsvSwatch;
    QColor rgb;
    QEngravedList *zoneButtons;
    Light *getLight() { return this->light; }

    QEngravedPushButton *btnSetPreset;
    QEngravedPushButton *btnSetOff;
    QEngravedPushButton *btnBack;

public slots:
    void updateFromWheel(QColor qcol);
    void sliderChanged(int val);

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
    Zone *zone;
    Light *light;
    QCheckBox *chkWhiteEnabled;
    QSlider *sl_whitelevel;

};
*/
#endif // LIGHTCONTROLWIDGET_H
