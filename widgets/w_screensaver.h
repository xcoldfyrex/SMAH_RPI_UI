#ifndef W_SCREENSAVER_H
#define W_SCREENSAVER_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>

class ScreenSaverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenSaverWidget(QWidget *parent = nullptr);
    QWidget *topWidget;

private:
    QLabel *lblClock;
    QHBoxLayout *topWidgetLayout;

private slots:
    void showTime();
};


#endif // W_SCREENSAVER_H
