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
    explicit TopHeaderWidget(QWidget *parent = 0, const char *name = 0 );
    QWidget *topWidget;

private:
    QLabel *lblClock;
    QPushButton *btnHome;
    QPushButton *btnInfo;
    QSpacerItem *spcHeader;
    QHBoxLayout *topWidgetLayout;
    QLabel *lblPath;

signals:

public slots:
};

#endif // HCHEADER_H
