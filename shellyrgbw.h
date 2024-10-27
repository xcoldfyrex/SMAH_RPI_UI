#ifndef SHELLYRGBW_H
#define SHELLYRGBW_H

#include "qtcpsocket.h"
#include <QObject>
#include <QHostAddress>

class ShellyRGBW : public QObject
{
public:
    ShellyRGBW(QString ip, QString mDNS);
    void setRGBW(int r, int g, int b, int w);

public slots:
    void readyRead();
    void disconnected();
    void socketError();

private:
    QString mDNS;
    QHostAddress ip;
    QTcpSocket *tcpSocket;
    bool connectShelly();
    bool disconnectShelly();
    quint16 blockSize = 0;
};

#endif // SHELLYRGBW_H
