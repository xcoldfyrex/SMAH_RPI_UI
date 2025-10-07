#include "shellyrgbw.h"
#include "QtCore"

QT_USE_NAMESPACE

ShellyRGBW::ShellyRGBW(QString ip, QString mDNS, QObject *parent) :
    QObject(parent)
{
    this->mDNS = mDNS;
    this->ip = ip;
    connect(&m_webSocket, &QWebSocket::connected, this, &ShellyRGBW::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ShellyRGBW::closed);
    QUrl url = QUrl("ws://" + ip + ":80/rpc/RGBW.Set?");
    this->url = QString(url.toString());
    doConnect();
}

void ShellyRGBW::doConnect()
{
        m_webSocket.open(url);
}

void ShellyRGBW::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ShellyRGBW::onTextMessageReceived);
    qInfo() << "Connected to Shelly" << this->mDNS << this->m_webSocket.peerAddress().toString();
    getStatus();
}

void ShellyRGBW::closed()
{
    qInfo() << "Connection to shelly closed. Retrying " + this->url;
    doConnect();
}

void ShellyRGBW::onTextMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc["id"] == 99) {
        //qDebug() << "Message received:" << doc;
        QJsonObject jsonObj = doc.object();
        QJsonValue jsonArray = jsonObj["result"];
        this->setLastUpdate(QDateTime::currentSecsSinceEpoch());
        //qDebug() << jsonArray;
        this->lastMessage = jsonArray;
        //qDebug() << this->lastMessage;
        emit(messageRecv());
    }
}

void ShellyRGBW::setRGBW(int r, int g, int b, int w, int brightness, bool state) {
    //qDebug() << this->mDNS << this->m_webSocket.peerAddress() << this->m_webSocket.state();
    if (this->m_webSocket.state() ==  QAbstractSocket::SocketState::ConnectedState) {
        QJsonObject payload;
        QJsonObject params;
        QJsonArray arr;
        arr.append(r);
        arr.append(g);
        arr.append(b);
        payload["method"] = "RGBW.Set";
        payload["id"] = 0;
        params["on"] = "true";
        params["id"] = "0";
        params["brightness"] = "100";
        params["rgb"] = arr;
        params["white"] = w;
        payload["params"] = params;
        m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
        //qDebug() << payload;
        getStatus();
    }
}

void ShellyRGBW::getStatus() {
    QJsonObject payload;
    QJsonObject params;
    QJsonArray arr;
    payload["method"] = "RGBW.GetStatus";
    payload["id"] = 99;
    params["id"] = "0";
    payload["params"] = params;
    m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
}
