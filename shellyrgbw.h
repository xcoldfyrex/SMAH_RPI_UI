#ifndef SHELLYRGBW_H
#define SHELLYRGBW_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

class ShellyRGBW : public QObject
{
    Q_OBJECT
public:
    //ShellyRGBW(QString ip, QString mDNS);
    explicit ShellyRGBW(const QUrl &url, QString mDNS, QObject *parent = nullptr);
    void setRGBW(int r, int g, int b, int w, int brightness, bool state);

private:
    QString mDNS;
    QWebSocket m_webSocket;
    bool m_debug;

//Q_SIGNALS:
//    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
    void closed();



};


#endif // SHELLYRGBW_H
