#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <QTimer>
#include <QObject>

class QUdpSocket;

class DatagramHandler : public QObject
{
    Q_OBJECT
public:
    explicit DatagramHandler();

private:
    QUdpSocket *udpSocket = nullptr;
    QUdpSocket *udpSocketBcast = nullptr;
    QTimer timer;
    void broadcastDatagram();

private slots:
    void processPendingDatagrams();
};

#endif // BROADCASTER_H
