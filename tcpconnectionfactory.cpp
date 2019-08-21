#include "tcpconnectionfactory.h"
#include <QDebug>

extern QList<ClientSocket*> g_clientMap;

TCPConnectionFactory::TCPConnectionFactory(QObject *parent)
    : QTcpServer(parent)
{

}

void TCPConnectionFactory::incomingConnection(qintptr socketDescriptor)
{
    //for (ClientSocket *socket : g_clientMap){

    //}
    //ClientSocket *socket = new ClientSocket(socketDescriptor, this);
    //connect(socket,SIGNAL(socketDisconnected(ClientSocket*)), this, SLOT(cleanSocket(ClientSocket*)));
    //connect(this,SIGNAL(broadcastSignal(QString, QJsonObject)), socket,SLOT(prepareToSend(QString,QJsonObject)));
    //g_clientMap.append(socket);
}

void TCPConnectionFactory::initiateConnection(QHostAddress *address)
{
    ClientSocket *socket = new ClientSocket(address, Q_NULLPTR);
    connect(socket,SIGNAL(socketDisconnected(ClientSocket*)), this, SLOT(cleanSocket(ClientSocket*)));
    connect(this,SIGNAL(broadcastSignal(QString, QJsonObject)), socket,SLOT(prepareToSend(QString,QJsonObject)));
    g_clientMap.append(socket);
    for (ClientSocket *sock : g_clientMap)
    {
        qDebug() << sock->getPeerAddress();
    }
}

void TCPConnectionFactory::cleanSocket(ClientSocket *socket)
{
    //clientMap
    int i = 0;
    foreach (ClientSocket *sock, g_clientMap)
    {
        if (sock->getPeerAddress() == socket->getPeerAddress())
        {
            //if (!sock->isHID)
            //zoneStatusChanged(clientMap.value(i)->clientID, 0);
            g_clientMap.removeAt(i);
            for (ClientSocket *sock : g_clientMap)
            {
                qDebug() << sock->getPeerAddress();
            }
            return;
        }
        i++;
    }

}
void TCPConnectionFactory::devReady(RPIDevice *device)
{
    emit deviceReady(device);
}

void TCPConnectionFactory::devLost(RPIDevice *device)
{
    emit deviceLost(device);
}

void TCPConnectionFactory::startListen()
{
    if (!this->listen(QHostAddress::AnyIPv4,9002)) {
        qWarning() << "Error opening listening socket";
    }
    outstanding = new QMap<QString, int>();
}

void TCPConnectionFactory::broadcastMessage(int srcDevice, int type, float value, int index)
{
    QJsonObject jsonPayload;
    jsonPayload["value"] = value;
    jsonPayload["id"] = srcDevice;
    jsonPayload["type"] = type;
    jsonPayload["index"] = index;
    emit broadcastSignal("UPDATE", jsonPayload);
}
