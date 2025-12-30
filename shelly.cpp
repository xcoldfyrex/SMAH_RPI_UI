#include "shelly.h"
#include "QtCore"
#include "qnetworkaccessmanager.h"
#include "qnetworkreply.h"

QT_USE_NAMESPACE

Shelly::Shelly(QString ip, QString mDNS, QString type, QObject *parent) :
    QObject(parent)
{
    this->mDNS = mDNS;
    this->ip = ip;
    connect(&m_webSocket, &QWebSocket::connected, this, &Shelly::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Shelly::closed);
    QUrl url = QUrl("ws://" + ip + ":80/rpc/RGBW.Set?");
    this->url = QString(url.toString());
    this->type = type;
    pollConfig();
    doConnect();
    getStatus();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=] {
        pollConfig();
        getStatus();
    });
    timer->start(10000);
}

void Shelly::getStatus()
{
    QJsonObject payload;
    QJsonObject params;
    QJsonArray arr;
    if (this->app == "Plus1PM") {
        payload["method"] = "Switch.GetStatus";
    } else if (this->app == "PlusRGBWPM") {
        payload["method"] = "RGBW.GetStatus";
    } else if (this->app == "PlusWallDimmer") {
        payload["method"] = "Light.GetStatus";
    }
    payload["id"] = 99;
    params["id"] = "0";
    payload["params"] = params;
    m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
}

void Shelly::doConnect()
{
    m_webSocket.open(url);
}

void Shelly::pollConfig()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager, &QNetworkAccessManager::finished,
                     this, [=](QNetworkReply *reply) {
                         if (reply->error()) {
                             qDebug() << reply->errorString();
                             return;
                         }
                         QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
                         this->ver = doc["ver"].toString();
                         this->app = doc["app"].toString();
                         this->model = doc["model"].toString();
                         this->name = doc["name"].toString();
                         manager->deleteLater();
                     }
                     );
    manager->get(QNetworkRequest(QUrl("http://" + ip + ":80/shelly")));
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
        this->lastMessage = jsonArray;
        this->state = this->lastMessage["output"].toBool(false);
        this->brightness = this->lastMessage["brightness"].toInt(0);
        this->ready = true;

        emit(messageRecv());
    } else {
        //qDebug() << "Message received:" << doc;
    }
}

void Shelly::closed()
{
    qInfo() << "Connection to shelly closed. Retrying " + this->url;
    doConnect();
}

/* END OF GENERIC FUNCTIONS */

void Shelly::setRGBW(int r, int g, int b, int w) {
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

void Shelly::setRGBW(QString color)
{
    bool ok;
    int r = color.mid(0,2).toInt(&ok, 16);
    int g = color.mid(2,2).toInt(&ok, 16);
    int b = color.mid(4,2).toInt(&ok, 16);
    int w = color.mid(6,2).toInt(&ok, 16);
    this->setRGBW(r, g, b, w);
}

void Shelly::setValue(QString type, QString val, bool on = true)
{
    if (this->m_webSocket.state() ==  QAbstractSocket::SocketState::ConnectedState) {
        QJsonObject payload;
        QJsonObject params;
        payload["method"] = "RGBW.Set";
        payload["id"] = 0;
        params["on"] = on;
        params["id"] = "0";
        params[type] = val;
        payload["params"] = params;
        m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
        getStatus();
    }
}

void Shelly::setState(bool on) {
    if (this->m_webSocket.state() ==  QAbstractSocket::SocketState::ConnectedState) {
        QJsonObject payload;
        QJsonObject params;
        if (this->app == "Plus1PM") {
            payload["method"] = "Switch.Set";
        } else if (this->app == "PlusRGBWPM") {
            payload["method"] = "RGBW.Set";
        } else if (this->app == "PlusWallDimmer") {
            payload["method"] = "Light.Set";
        }
        payload["id"] = 0;
        params["on"] = on;
        params["id"] = "0";
        payload["params"] = params;
        m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
        getStatus();
    }
}

void Shelly::setBrightness(int brightness) {
    if (this->m_webSocket.state() ==  QAbstractSocket::SocketState::ConnectedState) {
        QJsonObject payload;
        QJsonObject params;
        payload["method"] = "Light.Set";
        payload["id"] = 0;
        params["brightness"] = brightness;
        params["id"] = "0";
        payload["params"] = params;
        m_webSocket.sendTextMessage(QJsonDocument(payload).toJson(QJsonDocument::Compact));
        getStatus();
    }
}
