#ifndef RSSLISTING_H
#define RSSLISTING_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QUrl>

class RSSListing : public QObject
{
    Q_OBJECT
public:
    RSSListing();

public slots:
    void fetch(QString uri);
    void finished(QNetworkReply *reply);
    void readyRead();
    void metaDataChanged();
    void error(QNetworkReply::NetworkError);

private:
    void parseXml();
    void get(const QUrl &url);

    QXmlStreamReader xml;
    QString currentTag;
    QString linkString;
    QString titleString;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;

    bool hasSkipped = false;
};

#endif
