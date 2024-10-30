#include "shellyrgbw.h"
#include "QtCore"

//ShellyRGBW::ShellyRGBW(QString ip, QString mDNS) {
//    this->ip = QHostAddress(ip);
//    this->mDNS = mDNS;
//}

QT_USE_NAMESPACE

ShellyRGBW::ShellyRGBW(const QUrl &url, QString mDNS, QObject *parent) :
    QObject(parent)
{
    //if (m_debug)
    qDebug() << "WebSocket server:" << url;
    this->mDNS = mDNS;
    connect(&m_webSocket, &QWebSocket::connected, this, &ShellyRGBW::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ShellyRGBW::closed);
    m_webSocket.open(url);
}

void ShellyRGBW::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ShellyRGBW::onTextMessageReceived);
    qDebug() << this->m_webSocket.state();
    qDebug() << this->mDNS << this->m_webSocket.peerAddress();

}

void ShellyRGBW::onTextMessageReceived(QString message)
{
    //QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    //QJsonValue event = doc["event"];

    qDebug() << "Message received:" << message;

}

void ShellyRGBW::setRGBW(int r, int g, int b, int w, int brightness, bool state) {
    qDebug() << this->mDNS << this->m_webSocket.peerAddress() << this->m_webSocket.state();
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
        qDebug() << payload;

    }
}

void ShellyRGBW::closed()
{
    qDebug() << "CLOSED";
}
