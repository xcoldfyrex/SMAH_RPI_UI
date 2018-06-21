#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <sys/time.h>
#include <QDebug>
#include <QSslSocket>
#include <QMap>
#include <QTimer>
#include <QDataStream>
#include <QNetworkAddressEntry>

#include "zone2.h"
#include "preset.h"


class TCPConnection: public QObject
{
    Q_OBJECT

public:
    TCPConnection(QObject *parent = NULL);
    TCPConnection();
    bool isConnected();
    QString getIp_addr();
    void start(QHostAddress address);

public slots:
    void GPIOPoll();

private slots:
    void processPayload(QByteArray &buffer, QDataStream &payload);
    void socketConnect(QHostAddress addr);
    void socketError();
    void socketRead();
    void socketDisconnect();
    void enviroPoll();
    QJsonObject makeJsonObject(QByteArray buffer);


signals:
    void error(QTcpSocket::SocketError socketError);
    void zoneDiscovered(Zone zone);
    void presetArrived(Preset preset);
    void zoneGPIOArrived(QJsonObject payload, int zone);
    void zoneStatusChanged(int id, bool status);
    void powerFunctionsArrived();

private:
    int socketDescriptor;
    QString address;
    quint16 port;
    QTcpSocket *tcpSocket;
    int errcnt;
    QTimer *reconnectTimer;
    QTimer *enviroTimer;

    QMap<QString,QString>outstanding;
    quint16 blockSize;
};

#endif // NETWORK_H
