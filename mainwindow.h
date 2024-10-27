#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedLayout>
#include <QMap>
#include <QTimer>
#include <QPainter>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *pe);
    QWidget *topWidget;
    QStackedLayout *contentLayout;

private:
    QStackedLayout *mainWidgetLayout;
    QTimer *idleTimer;

protected:

signals:
    //void zoneChanged(Zone*);
    //void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);

public slots:
    void hideSaver();
    void showSaver();
    void resetIdle(QEvent *ev);
};

#endif // MAINWINDOW_H
