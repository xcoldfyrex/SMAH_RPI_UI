#include "zwavesocket.h"
#include "sensor.h"

#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

extern QList <Sensor*> g_sensorList;
QT_USE_NAMESPACE

//! [constructor]
ZWaveSocket::ZWaveSocket(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &ZWaveSocket::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &ZWaveSocket::closed);
    m_webSocket.open(url);
}
//! [constructor]

//! [onConnected]
void ZWaveSocket::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &ZWaveSocket::onTextMessageReceived);
    QJsonObject start;
    start["messageId"] = "foobar";
    start["command"] = "start_listening";
    m_webSocket.sendTextMessage(QJsonDocument(start).toJson(QJsonDocument::Compact));
}
//! [onConnected]

//! [onTextMessageReceived]
void ZWaveSocket::onTextMessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonValue event = doc["event"];
    if (event["event"] == "value updated" && event["source"] == "node") {
        QJsonValue args = event["args"];
        foreach (Sensor *sensor, g_sensorList) {
            if (event["nodeId"] == sensor->getNodeId() ) {
                if (args["commandClass"] == 49) {
                    if (args["propertyName"] == "Humidity")
                        sensor->setValue(5, float(args["newValue"].toDouble()));
                    if (args["propertyName"] == "Air temperature")
                        sensor->setValue(1, float(args["newValue"].toDouble()));
                    if (args["propertyName"] == "Illuminance")
                        sensor->setValue(3, float(args["newValue"].toDouble()));
                    if (args["propertyName"] == "Ultraviolet")
                        sensor->setValue(27, float(args["newValue"].toDouble()));
                }
            }
        }
        if (m_debug)
            qDebug() << "Message received:" << event;
    }
    // m_webSocket.close();
}
