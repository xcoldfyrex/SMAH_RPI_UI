#include <QtNetwork>
#include <QDebug>

#include "datagramhandler.h"
#include "tcpsocket.h"

extern QList<ClientSocket*> g_clientMap;

DatagramHandler::DatagramHandler()
{
    udpSocket = new QUdpSocket(this);
    udpSocketBcast = new QUdpSocket(this);
    QHostAddress *bcast = new QHostAddress("0.0.0.0");
    udpSocket->bind(*bcast, 9003, QUdpSocket::ShareAddress);

    connect(&timer, &QTimer::timeout, this, &DatagramHandler::broadcastDatagram);
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
    timer.start(5000);
}

void DatagramHandler::broadcastDatagram()
{
    QByteArray datagram = "__SMAH__";
    udpSocketBcast->writeDatagram(datagram, QHostAddress::Broadcast, 9003);
}

void DatagramHandler::processPendingDatagrams()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QByteArray datagram;
    QHostAddress *address = new QHostAddress();
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size(),address);
        if (list.contains(*address))
            break;
        if (QString(datagram.constData()) == "__SMAH__")
            // goat a HELLO
        {
            //qInfo() << "Got HELLO from" << *address;
            //check to see ifit's already pending in the map and drop ifso
            if ( g_clientMap.size() != 0)
            {
                for (ClientSocket *sock : g_clientMap)
                {
                    if (sock->getPeerAddress() == *address)
                    {
                        return;
                    }
                }
            }
            ClientSocket *client = new ClientSocket(*address, NULL);
            g_clientMap.append(client);
        }
    }
}