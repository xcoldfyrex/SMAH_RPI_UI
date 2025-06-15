#ifndef ZWAVESOCKET_H
#define ZWAVESOCKET_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class ZWaveSocket : public QObject
{
    Q_OBJECT
public:
    explicit ZWaveSocket(const QUrl &url, bool debug = false, QObject *parent = nullptr);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onClosed();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    bool m_debug;
    QUrl url;
    void doConnect();
};

#endif // ZWAVESOCKET_H
