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
    explicit ClientSocket(QTcpSocket *ID, QObject *parent);
    ClientSocket(QHostAddress address, QObject *parent);
    QHostAddress getPeerAddress() { return this->remoteAddress; }
    //RPIDevice *getDevice() { return this->rpidevice; }
    QString getDeviceID() { return this->devid; }
    int getRPIDeviceID() { return this->rpidevice->getId(); }
    void prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo);


public slots:
    void readyRead();
    void disconnected();
    void socketError();
    void prepareToSend(QString command, QJsonObject jsonPayload);

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
    QString devid = "";
    QHostAddress remoteAddress;
    RPIDevice *rpidevice;
    void send_id(QJsonObject data);
    void sendData(QJsonObject data);
    void processPayload(QByteArray buffer);
    bool hasSentID = false;

    QJsonObject buildPayload();

};

#endif // TCPSOCKET_H
