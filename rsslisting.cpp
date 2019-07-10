#include <QtNetwork>

#include "rsslisting.h"

/*
    Constructs an RSSListing widget with a simple user interface, and sets
    up the XML reader to use a custom handler class.

    The user interface consists of a line edit, a push button, and a
    list view widget. The line edit is used for entering the URLs of news
    sources; the push button starts the process of reading the
    news.
*/

RSSListing::RSSListing()
    : QObject(), currentReply(Q_NULLPTR)
{

    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));


}

/*
    Starts the network request and connects the needed signals
*/
void RSSListing::get(const QUrl &url)
{
    QNetworkRequest request(url);
    if (currentReply) {
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }
    request.setRawHeader("User-Agent","Fake User");
    currentReply = manager.get(request);
    connect(currentReply, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(currentReply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
    connect(currentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

/*
    Starts fetching data from a news source specified in the line
    edit widget.

    The line edit is made read only to prevent the user from modifying its
    contents during the fetch; this is only for cosmetic purposes.
    The fetch button is disabled, the list view is cleared, and we
    define the last list view item to be 0, meaning that there are no
    existing items in the list.

    A URL is created with the raw contents of the line edit and
    a get is initiated.
*/

void RSSListing::fetch(QString uri)
{
    xml.clear();
    QUrl url(uri);
    get(url);
}

void RSSListing::metaDataChanged()
{
    QUrl redirectionTarget = currentReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (redirectionTarget.isValid()) {
        get(redirectionTarget);
    }
}

/*
    Reads data received from the RDF source.

    We read all the available data, and pass it to the XML
    stream reader. Then we call the XML parsing function.
*/

void RSSListing::readyRead()
{
    int statusCode = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode >= 200 && statusCode < 300) {
        QByteArray data = currentReply->readAll();
        xml.addData(data);
        parseXml();
    }
}

/*
    Finishes processing an HTTP request.

    The default behavior is to keep the text edit read only.

    If an error has occurred, the user interface is made available
    to the user for further input, allowing a new fetch to be
    started.

    If the HTTP get request has finished, we make the
    user interface available to the user for further input.
*/

void RSSListing::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);
}

/*
    Parses the XML data and creates treeWidget items accordingly.
*/
void RSSListing::parseXml()
{
    while (!xml.atEnd()) {
        xml.readNext();
        if (xml.isStartElement()) {
            if (xml.name() == "item"){
                //linkString = xml.attributes().value("rss:about").toString();
            }
            currentTag = xml.name().toString();
        } else if (xml.isEndElement()) {
            if (xml.name() == "item") {
                titleString.clear();
                linkString.clear();
            }

        } else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (currentTag == "title")
            {
                if (!hasSkipped)
                {
                    hasSkipped = true;
                } else {
                    titleString += xml.text().toString();
                    qDebug() << titleString;
                }
            }
        }
    }
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
    }
}

void RSSListing::error(QNetworkReply::NetworkError)
{
    //QString reason = currentReply->attribute(QNetworkRequest::HttpReasonPhraseAttribute ).toString();
    QString reason = currentReply->errorString().toStdString().c_str();
    qWarning() << "error retrieving RSS feed" << reason;
    currentReply->disconnect(this);
    currentReply->deleteLater();
    currentReply = 0;
}
