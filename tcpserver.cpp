#include "tcpserver.h"
#include <QDebug>

extern QList<ClientSocket*> g_clientMap;

TCPServer::TCPServer(QObject *parent)
    : QTcpServer(parent)
{
    if (!this->listen(QHostAddress::Any,9002)) {
        qWarning() << "Error opening listening socket";
    }
    outstanding = new QMap<QString, int>();
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    ClientSocket *socket = new ClientSocket(socketDescriptor, this);
    connect(socket,SIGNAL(socketDisconnected(ClientSocket*)), this, SLOT(cleanSocket(ClientSocket*)));
    g_clientMap.append(socket);
}


void TCPServer::cleanSocket(ClientSocket *socket)
{
    int i = 0;
    foreach (ClientSocket *sock, g_clientMap)
    {
        //if (sock->clientID == socket->clientID)
        //{
            //if (!sock->isHID)
                //zoneStatusChanged(clientMap.value(i)->clientID, 0);
          //  clientMap.removeAt(i);
            //return;
        //}
        //i++;
    }

}

