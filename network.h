#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <sys/time.h>
#include <QDebug>

class NetworkThread: public QThread
{
    Q_OBJECT

public:
    explicit NetworkThread(QString address, quint16 port, QObject *parent);
    bool isConnected();
    void run();


public slots:
    void readyRead();
    void disconnected();
    void sendData(QJsonObject data);
    void sendPing();
    void sendStart();
    QJsonObject buildPayload();

private slots:
    void processPayload(QJsonObject data);

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString address;
    quint16 port;
    QTcpSocket *socket;
};

#endif // NETWORK_H
