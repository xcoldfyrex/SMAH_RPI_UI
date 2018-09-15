#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QMap>
#include <QHostAddress>

#include "tcpsocket.h"

class TCPServer : public QTcpServer
{
    Q_OBJECT
public:
    TCPServer(QObject *parent = 0);
    QMap<QString, int> *outstanding;

protected:
    void incomingConnection(qintptr socketDescriptor);

public slots:
    void cleanSocket(ClientSocket *socket);

};

#endif // TCPSERVER_H
