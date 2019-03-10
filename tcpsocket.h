#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QThread>
#include <QTcpSocket>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>
#include <QDataStream>
#include <QHostAddress>

#include <rpidevice.h>

class ClientSocket : public QObject
{
    Q_OBJECT

public:
    explicit ClientSocket(qintptr ID, QObject *parent);
    ClientSocket(QHostAddress address, QObject *parent);
    QHostAddress getPeerAddress() { return this->remoteAddress; }
    //RPIDevice *getDevice() { return this->rpidevice; }
    int getDeviceID() { return this->devid; }
    void prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo);
    void prepareToSend(QString command, QJsonObject jsonPayload);


public slots:
    void readyRead();
    void disconnected();
    void socketError();

signals:
    void error(QTcpSocket::SocketError socketError);
    void socketDisconnected(ClientSocket *tcpSocket);
    void deviceArrived(RPIDevice *device);

private:
    int socketDescriptor;
    QTcpSocket *tcpSocket;
    long lastPong;
    QTimer *pingTimer;
    std::string peer_address;
    quint16 blockSize;
    QObject *parent;
    int devid = 0;
    QHostAddress remoteAddress;
    RPIDevice *rpidevice;
    void send_id(QTcpSocket *tcpSocket, QJsonObject data);
    void sendData(QJsonObject data);
    void processPayload(QByteArray buffer);

    QJsonObject buildPayload();

};

#endif // TCPSOCKET_H
