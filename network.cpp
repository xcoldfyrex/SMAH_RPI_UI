#include "network.h"

Network::Network(QObject* parent): QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
}

void Network::start(QString address, quint16 port) {
    QHostAddress addr(address);
    tcpSocket->connectToHost(addr, port);
}

void Network::networkOut() {

}
