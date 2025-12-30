#include "shellyrgbw.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

ShellyRGBW::ShellyRGBW(QString ip, QString mDNS, QString type, QObject *parent)
    : Shelly{ip,  mDNS, type, parent}
{
    this->ip = ip;
    this->mDNS = mDNS;
}

void ShellyRGBW::setRGBW(int r, int g, int b, int w) {
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

void ShellyRGBW::setRGBW(QString color)
{
    bool ok;
    int r = color.mid(0,2).toInt(&ok, 16);
    int g = color.mid(2,2).toInt(&ok, 16);
    int b = color.mid(4,2).toInt(&ok, 16);
    int w = color.mid(6,2).toInt(&ok, 16);
    this->setRGBW(r, g, b, w);
}

void ShellyRGBW::setValue(QString type, QString val, bool on = true)
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
