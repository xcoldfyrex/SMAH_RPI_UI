#ifndef LIGHTCONTROLWIDGET_H
#define LIGHTCONTROLWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QPicture>

#include "w_hslswatch.h"
#include "w_colorpreview.h"
#include "mainwindow.h"
#include "zone.h"


namespace Ui {
class LightControlWidget;
}

class LightControlContainerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightControlContainerWidget(Zone *zone, QWidget *parent = 0);
    ~LightControlContainerWidget();
    QWidget *topWidget;
    QWidget *colorPalette;
    ColorPreview *preview;
    QGridLayout *contentLayout;
    QPicture *hsvSwatch;
    QColor rgb;
//signals:
//    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void updateFromWheel(QColor qcol);
    void updateFromSwatch(QColor qcol);

private:
    Ui::LightControlWidget *ui;
    QGraphicsScene *scene;
    HSLSwatch *hslSwatch;
    Zone *zone;
};

#endif // LIGHTCONTROLWIDGET_H
