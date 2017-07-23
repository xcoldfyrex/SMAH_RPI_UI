#include "network.h"
#include "libsmah_network.h"


extern QMap<int, Zone*> *gZoneMap;

QByteArray socketBuffer;

NetworkThread::NetworkThread(QString address, quint16 port, QObject *parent)
    : QObject(parent)
{
    this->address = address;
    this->port = port;
    this->blockSize = 0;
    tcpSocket = new QTcpSocket();

    reconnectTimer = new QTimer();
    reconnectTimer->setInterval(5000);

    enviroTimer = new QTimer();
    enviroTimer->setInterval(5000);

    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(socketConnect()),Qt::DirectConnection);
    connect(enviroTimer, SIGNAL(timeout()), this, SLOT(enviroPoll()),Qt::DirectConnection);

    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(socketRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(socketDisconnect()),Qt::DirectConnection);
    errcnt = 0;
    socketConnect();
}

NetworkThread::NetworkThread() {

}

void NetworkThread::socketConnect()
{
    QHostAddress addr(this->address);
    qInfo() << "Connecting to" << addr.toString() << this->port;
    tcpSocket->connectToHost(addr, this->port);
    if (tcpSocket->waitForConnected(5000))
    {
        reconnectTimer->stop();
        smah::sendStart(tcpSocket);
    }
}

void NetworkThread::socketRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_5_0);

    QByteArray buffer;


    while( true )
    {
        if( blockSize == 0 )
        {
            if( (quint16) tcpSocket->bytesAvailable() < sizeof(quint16) )
                return;
            in >> blockSize;
        }


        if (tcpSocket->bytesAvailable() < (int) blockSize)
            return;

        in >> buffer;
        qDebug() << "IN" << buffer;

        processPayload(buffer);
        blockSize = 0;

    }
}


void NetworkThread::socketDisconnect()
{
    qDebug() << socketDescriptor  << "CLOSED" <<  tcpSocket->peerAddress().toString();
}

void NetworkThread::socketError()
{
    qWarning() << "Socket error:" << tcpSocket->errorString().toStdString().c_str();
    if (!reconnectTimer->isActive())
    {
        reconnectTimer->start();
        enviroTimer->stop();
    }
}

void NetworkThread::processPayload(QByteArray buffer)
{
    QJsonDocument doc = QJsonDocument::fromJson(buffer.data());
    if(doc.isNull())
    {
        qDebug() << socketDescriptor << "ERROR Invalid JSON...";
        return;
    }

    QJsonObject data = doc.object();
    QString command = data.value("command").toString();

    //start negotiation
    if (command == "START" )
    {
        smah::send_id(tcpSocket, data);
    }

    //negotiated
    if (command == "OK" )
    {
        get_zones();
        get_presets();
        enviroTimer->start();
    }

    //server responded to a GET_RESOURCE or GET
    if (command == "RESPOND" )
    {
        QString id = data.value("responseTo").toString();
        int zone = data.value("zone").toInt();

        if (outstanding.contains(id))
        {
            QString type = outstanding.value(id);
            if (type == "ZONES")
            {
                QJsonArray array = data.value("payload").toArray();
                int envZones = 0;
                int controlZones = 0;
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    if (gZoneMap->size() > 0)
                    {
                        foreach (Zone *zone, *gZoneMap)
                        {
                            if (zone->id == obj["id"].toInt())
                                return;
                        }
                    }
                    bool hasEnviro = obj["hasEnviro"].toString().contains("true");
                    bool hasRGB = obj["hasLedRGB"].toString().contains("true");
                    bool hasPower = obj["hasPower"].toString().contains("true");
                    bool hasLedWhite = obj["hasLedWhite"].toString().contains("true");
                    QString zoneName = obj["name"].toString();
                    Zone *zone = new Zone(obj["id"].toInt(), zoneName, hasRGB, hasLedWhite, hasPower, hasEnviro);
                    gZoneMap->insert(zone->id, zone);
                    emit zoneDiscovered(zone, envZones, controlZones);

                    if (hasEnviro) {
                        envZones++;
                    }

                    if (hasRGB || hasLedWhite || hasPower) {
                        controlZones++;
                    }

                }
            }

            if (type == "PRESETS")
            {
                QJsonArray array = data.value("payload").toArray();
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    int presetID = obj["id"].toInt();
                    Preset *preset = new Preset(obj["name"].toString(),presetID);
                    emit presetArrived(preset);
                }
            }

            if (type == "MCP320X")
            {
                QJsonObject payload = data.value("payload").toObject();
                emit zoneResourceArrived(payload, zone);
                //qDebug() << data;
            }
            outstanding.remove(id);
        }

    }

    if (command == "ZONE" )
    {
        foreach (Zone *zone, *gZoneMap)
        {
            if (zone->id == data.value("zone").toInt())
            {
                if (data.value("status").toInt() == 1)
                {
                    zone->zoneSelector->setEnabled(true);
                } else {
                    zone->zoneSelector->setEnabled(false);
                }
            }
        }
    }

}


// LIBSMAH ??

void NetworkThread::get_presets()
{
    QJsonObject jsonObject = smah::buildPayload();
    jsonObject["command"] = "GET_RESOURCE";
    jsonObject["resource"] = "PRESETS";
    outstanding.insert(jsonObject["requestID"].toString(), jsonObject["resource"].toString());
    smah::socket_write(jsonObject, tcpSocket);
}

// LIBSMAH ??

void NetworkThread::get_zones()
{
    QJsonObject jsonObject = smah::buildPayload();
    jsonObject["command"] = "GET_RESOURCE";
    jsonObject["resource"] = "ZONES";
    outstanding.insert(jsonObject["requestID"].toString(), jsonObject["resource"].toString());
    smah::socket_write(jsonObject, tcpSocket);
}

/* wrapper for signals to reference */
void NetworkThread::prepareToSendWrapper(QString string1, QJsonObject jso1, QString string2)
{
    smah::prepareToSend(string1, jso1, tcpSocket, string2);
}

void NetworkThread::enviroPoll()
{
    foreach (Zone *zone, *gZoneMap) {
        if (zone->hasEnviro) {
            QJsonObject jsonObject = smah::buildPayload();
            jsonObject["command"] = "GET";
            jsonObject["resource"] = "MCP320X";
            jsonObject["zone"] = zone->id;

            outstanding.insert(jsonObject["requestID"].toString(), "MCP320X");
            smah::socket_write(jsonObject, tcpSocket);
        }
    }



}
