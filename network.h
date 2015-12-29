#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>

class Network: public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject* parent = 0);
    void start(QString address, quint16 port);

public slots:
    void networkOut();

private:
    QTcpSocket *tcpSocket;
};

#endif // NETWORK_H
