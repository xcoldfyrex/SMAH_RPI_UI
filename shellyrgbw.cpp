#include "shellyrgbw.h"
#include "QtCore"

ShellyRGBW::ShellyRGBW(QString ip, QString mDNS) {
    this->ip = QHostAddress(ip);
    this->mDNS = mDNS;
}

bool ShellyRGBW::connectShelly() {
    this->tcpSocket = new QTcpSocket();
    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    tcpSocket->close();
    connect(tcpSocket, &QAbstractSocket::connected,[]()
            {
                //QJsonObject data;
                return true;
            });

    tcpSocket->connectToHost(this->ip,80);
    return true;
}

void ShellyRGBW::readyRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_0);
    QByteArray buffer;

    while( true )
    {
        if( blockSize == 0 )
        {
            if( tcpSocket->bytesAvailable() < sizeof(quint16) )
                return;
            in >> blockSize;
        }

        if (tcpSocket->bytesAvailable() < static_cast<int>(blockSize))
            return;

        in >> buffer;
        //processPayload(buffer);
        blockSize = 0;
    }
}
