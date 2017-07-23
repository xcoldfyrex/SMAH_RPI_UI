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

#include "zone.h"
#include "libsmah_preset.h"


class NetworkThread: public QObject
{
    Q_OBJECT

public:
    NetworkThread(QString address, quint16 port, QObject *parent);
    NetworkThread();
    bool isConnected();

public slots:
    void prepareToSendWrapper(QString, QJsonObject, QString string2);

private slots:
    void processPayload(QByteArray buffer);
    void socketConnect();
    void socketError();
    void socketRead();
    void socketDisconnect();
    void get_zones();
    void get_presets();
    void enviroPoll();


signals:
    void error(QTcpSocket::SocketError socketError);
    void zoneDiscovered(Zone *zone, int envZones, int controlZones);
    void presetArrived(Preset *preset);
    void zoneResourceArrived(QJsonObject payload, int zone);
    void zoneStatusChanged(int id, bool status);

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
