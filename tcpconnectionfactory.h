#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QMap>
#include <QHostAddress>
#include <QJsonObject>

#include "tcpsocket.h"
#include "rpidevice.h"

class TCPConnectionFactory : public QObject
{
    Q_OBJECT
public:
    TCPConnectionFactory(QObject *parent = Q_NULLPTR);
    QMap<QString, int> *outstanding;
    void startListen();
    void broadcastMessage(int srcDevice, int type, float value, int index);
    void broadcastMessageJSON(QString type, QJsonObject data);

private:
    QTcpServer *server;
protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void cleanSocket(ClientSocket *socket);
    void devReady(RPIDevice *device);
    void devLost(RPIDevice *device);
    void newConnection();

signals:
    void deviceReady(RPIDevice *device);
    void deviceLost(RPIDevice *device);
    void broadcastSignal(QString data, QJsonObject payload);
};

#endif // TCPSERVER_H
