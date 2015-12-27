#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>

namespace Ui {
class MenuWindow;
}

class ZoneChooserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoneChooserWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *pe);
    QGridLayout *contentLayout;
    QWidget *topWidget;

private:
    //Ui::ZoneChooser *ui;
};

#endif // MENUWINDOW_H
