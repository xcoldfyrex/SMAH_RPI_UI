#ifndef SHELLY_H
#define SHELLY_H

#include "qjsonvalue.h"
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class Shelly : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getID CONSTANT)
    Q_PROPERTY(QString ip READ getIP CONSTANT)
    Q_PROPERTY(QString host READ getHost CONSTANT)
    Q_PROPERTY(QString url READ getURL CONSTANT)
    Q_PROPERTY(QJsonValue message READ getMessage NOTIFY messageRecv)
    Q_PROPERTY(QVariant updated READ getLastUpdate NOTIFY messageRecv)

public:
    explicit Shelly(QString ip, QString mDNS, QObject *parent = nullptr);
    QString getID() { return this->mDNS; }
    QString getURL() { return this->url; }
    QString getIP() { return QString(this->m_webSocket.peerAddress().toString()); }
    QString getHost() { return this->ip; }
    QJsonValue getMessage() { return this->lastMessage; }

    qint64 getLastUpdate() { return this->updated; }
    void setLastUpdate(qint64 ts) { this->updated = ts; }

protected:
    QString mDNS;
    QString ip;
    QString url;
    QJsonValue lastMessage;
    QWebSocket m_webSocket;
    void getStatus();
    qint64 updated = 0;
    void doConnect();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void closed();

signals:
    void messageRecv();

};


#endif // SHELLY_H
