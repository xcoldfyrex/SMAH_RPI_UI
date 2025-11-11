#include "shelly.h"
#include "QtCore"

QT_USE_NAMESPACE

Shelly::Shelly(QString ip, QString mDNS, QObject *parent) :
    QObject(parent)
{
    this->mDNS = mDNS;
    this->ip = ip;
    connect(&m_webSocket, &QWebSocket::connected, this, &Shelly::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Shelly::closed);
    QUrl url = QUrl("ws://" + ip + ":80/rpc/RGBW.Set?");
    this->url = QString(url.toString());
    doConnect();
}



void Shelly::getStatus() {
    QJsonObject payload;
    QJsonObject params;
    QJsonArray arr;
    payload["method"] = "RGBW.GetStatus";
    payload["id"] = 99;
    params["id"] = "0";
    payload["params"] = params;
    m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
}

void Shelly::doConnect()
{
        m_webSocket.open(url);
}

void Shelly::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Shelly::onTextMessageReceived);
    qInfo() << "Connected to Shelly" << this->mDNS << this->m_webSocket.peerAddress().toString();
    getStatus();
}

void Shelly::onTextMessageReceived(QString message)
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

void Shelly::closed()
{
    qInfo() << "Connection to shelly closed. Retrying " + this->url;
    doConnect();
}
