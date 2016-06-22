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

#include "zone.h"
#include "preset.h"


class NetworkThread: public QThread
{
    Q_OBJECT

public:
    NetworkThread(QString address, quint16 port, QObject *parent);
    NetworkThread();
    bool isConnected();
    void run();

public slots:
    void prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo);

private slots:
    void processPayload(QJsonObject data);
    void socketConnect();
    void socketError();
    void sendPing();
    void sendStart();
    void socketRead();
    void socketDisconnect();
    void socket_write(QJsonObject data);
    void get_zones();
    void get_presets();


signals:
    void error(QTcpSocket::SocketError socketError);
    void zoneArrived(Zone *zone);
    void presetArrived(Preset *preset);

private:
    int socketDescriptor;
    QString address;
    quint16 port;
    QTcpSocket *socket;
    QJsonObject buildPayload();
    int errcnt;
    QMap<QString,QString>outstanding;

};

#endif // NETWORK_H
