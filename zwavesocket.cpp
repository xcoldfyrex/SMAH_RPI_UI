#include "zwavesocket.h"
#include <QtCore/QDebug>

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
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}
//! [onConnected]

//! [onTextMessageReceived]
void ZWaveSocket::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
   // m_webSocket.close();
}
