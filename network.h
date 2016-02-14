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
#include <QSslSocket>

class NetworkThread: public QThread
{
    Q_OBJECT

public:
    explicit NetworkThread(QString address, quint16 port, QObject *parent);
    bool isConnected();
    void run();

public slots:


private slots:
    void processPayload(QJsonObject data);
    void socketConnect();
    void socketError();
    void sendPing();
    void sendStart();
    void socketRead();
    void socketDisconnect();
    void socketWrite(QJsonObject data);


signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
    QString address;
    quint16 port;
    QTcpSocket *socket;
    QJsonObject buildPayload();
    int errcnt;

};

#endif // NETWORK_H
