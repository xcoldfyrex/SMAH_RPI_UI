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
    Q_PROPERTY(QString app READ getApp NOTIFY messageRecv)
    Q_PROPERTY(QString ver READ getVer NOTIFY messageRecv)
    Q_PROPERTY(QString model READ getModel NOTIFY messageRecv)
    Q_PROPERTY(QString name READ getName NOTIFY messageRecv)
    Q_PROPERTY(QJsonValue message READ getMessage NOTIFY messageRecv)
    Q_PROPERTY(QJsonValue state READ getState NOTIFY messageRecv)
    Q_PROPERTY(QVariant updated READ getLastUpdate NOTIFY messageRecv)

public:
    explicit Shelly(QString ip, QString mDNS, QString type = "", QObject *parent = nullptr);
    QString getID() { return this->mDNS; }
    QString getURL() { return this->url; }
    QString getIP() { return QString(this->m_webSocket.peerAddress().toString()); }
    QString getHost() { return this->ip; }
    QString getApp() { return this->app; }
    QString getVer() { return this->ver; }
    QString getModel() { return this->model; }
    QString getName() { return this->name; }
    QJsonValue getMessage() { return this->lastMessage; }
    qint64 getLastUpdate() { return this->updated; }
    void setLastUpdate(qint64 ts) { this->updated = ts; }
    /* RGBW functions */
    void setRGBW(int r, int g, int b, int w);
    void setRGBW(QString color);
    void setValue(QString type, QString val, bool on);
    /* PM relay functions */
    void setState(bool on);
    bool getState() { return this->state; };
    bool isReady() { return this->ready; };
    /* Dimmer */
    void setBrightness(int brightness);
    int getBrightness() { return this->brightness; }

protected:
    /* read from hardware */
    QString type;
    QString app;
    QString ver;
    QString model;
    QString name;
    bool state = false;
    int brightness = 0;

    /* other stuff */
    QString mDNS;
    QString ip;
    QString url;
    QJsonValue lastMessage = "";
    QWebSocket m_webSocket;
    void getStatus();
    qint64 updated = 0;
    void doConnect();
    void pollConfig();
    bool ready = false;

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void closed();

signals:
    void messageRecv();

};


#endif // SHELLY_H
