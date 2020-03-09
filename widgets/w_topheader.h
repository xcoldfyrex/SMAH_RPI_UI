#ifndef HCHEADER_H
#define HCHEADER_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

class TopHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopHeaderWidget(QWidget *parent = nullptr, const char *name = nullptr);
    QWidget *topWidget;

private:
    QLabel *lblClock;
    QLabel *lblDate;
    QLabel *lblSunrise;
    QLabel *lblSunset;
    QPushButton *btnHome;
    QPushButton *btnInfo;
    QPushButton *btnWeather;
    QSpacerItem *spcHeader;
    QHBoxLayout *topWidgetLayout;
    QLabel *lblPath;

signals:

public slots:
    void showTime();
};

#endif // HCHEADER_H
