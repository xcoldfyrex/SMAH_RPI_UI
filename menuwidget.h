#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPaintEvent>
#include <QPainter>

namespace Ui {
class MenuWindow;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = 0);
    ~MenuWidget();
    void paintEvent(QPaintEvent *pe);
    QGridLayout *contentLayout;
    QWidget *topWidget;

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
