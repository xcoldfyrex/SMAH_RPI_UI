#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QMap>
#include <QHostAddress>

#include "tcpsocket.h"
#include "rpidevice.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer(QObject *parent = Q_NULLPTR);
    QMap<QString, int> *outstanding;
    void startListen();
    void broadcastMessage(int srcDevice, int type, float value, int index);

protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void cleanSocket(ClientSocket *socket);
    void devReady(RPIDevice *device);
    void devLost(RPIDevice *device);

signals:
    void deviceReady(RPIDevice *device);
    void deviceLost(RPIDevice *device);
    void broadcastSignal(QString data, QJsonObject payload);
};

#endif // TCPSERVER_H
