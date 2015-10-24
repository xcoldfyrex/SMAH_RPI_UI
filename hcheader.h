#ifndef HCHEADER_H
#define HCHEADER_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

class HCHeader : public QWidget
{
    Q_OBJECT
public:
    explicit HCHeader(QWidget *parent = 0, const char *name = 0 );
    QWidget *topWidget;

private:
    QLabel *lblClock;
    QPushButton *btnHome;
    QSpacerItem *spcHeader;
    QHBoxLayout *topWidgetLayout;
    QLabel *lblPath;

signals:

public slots:
};

#endif // HCHEADER_H
