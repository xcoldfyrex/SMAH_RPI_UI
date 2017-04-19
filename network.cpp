#include "network.h"

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

    connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(socketConnect()),Qt::DirectConnection);
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
    qDebug() << "Conencting to " << addr << this->port;
    tcpSocket->connectToHost(addr, this->port);
    if (tcpSocket->waitForConnected(5000))
    {
        reconnectTimer->stop();
        sendStart();
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
            if( tcpSocket->bytesAvailable() < sizeof(quint16) )
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

void NetworkThread::socket_write(QJsonObject data)
{
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        const char *c_str2 = ba.data();
        char buffer[128];
        sprintf(buffer, "%s\n\n", c_str2);

        tcpSocket->write(buffer);
        qDebug() << strlen(buffer) << "OUT" << buffer;
        tcpSocket->flush();
    }
}

void NetworkThread::socketDisconnect()
{
    qDebug() << socketDescriptor  << "CLOSED" <<  tcpSocket->peerAddress().toString();
}

void NetworkThread::socketError()
{
    qDebug() << "Socket error:" << errcnt << tcpSocket->errorString();
    if (!reconnectTimer->isActive())
        reconnectTimer->start();
}

void NetworkThread::sendStart()
{
    QJsonObject payloadStart = buildPayload();
    payloadStart["command"] = "START";
    socket_write(payloadStart);
}

void NetworkThread::sendPing()
{
    QJsonObject payloadStart = buildPayload();
    payloadStart["command"] = "PING";
    socket_write(payloadStart);
}

QJsonObject NetworkThread::buildPayload()
{
    char buffer[12];
    for(int i = 0; i < 11; i++) {
        sprintf(buffer + i, "%x", rand() % 16);
    }
    QJsonObject payloadOut;

    payloadOut["requestID"] = QString(buffer);
    return payloadOut;
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
        QJsonObject jsonPayload;
        jsonPayload["clientid"] = 100;
        prepareToSend("ID",jsonPayload,data.value("requestID").toString());
    }

    //negotiated
    if (command == "OK" )
    {
        this->get_zones();
        this->get_presets();
    }

    //server responded to a GET_RESOURCE
    if (command == "RESPOND" )
    {
        QString id = data.value("responseTo").toString();
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
                    QString zoneName = obj["name"].toString();
                    Zone *zone = new Zone(obj["id"].toInt(), zoneName, hasRGB, true, hasEnviro);
                    gZoneMap->insert(zone->id, zone);
                    emit zoneArrived(zone, envZones, controlZones);

                    if (hasEnviro) {
                        envZones++;
                    }

                    if (hasRGB) {
                        controlZones++;
                    }

                }
            }

            if (type == "PRESETS")
            {
                QJsonArray array = data.value("payload").toArray();
                qDebug() << data.value("payload");
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    int presetID = obj["id"].toInt();
                    Preset *preset = new Preset(obj["name"].toString(),presetID);
                    emit presetArrived(preset);
                }
            }
            outstanding.remove(id);
        }
    }
}

void NetworkThread::prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo = "")
{
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = command;
    jsonObject["payload"] = jsonPayload;
    if (responseTo != "") jsonObject["responseTo"] = responseTo;

    socket_write(jsonObject);
}

void NetworkThread::get_zones()
{
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = "GET_RESOURCE";
    jsonObject["resource"] = "ZONES";
    outstanding.insert(jsonObject["requestID"].toString(), jsonObject["resource"].toString());
    socket_write(jsonObject);
}


void NetworkThread::get_presets()
{
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = "GET_RESOURCE";
    jsonObject["resource"] = "PRESETS";
    outstanding.insert(jsonObject["requestID"].toString(), jsonObject["resource"].toString());
    socket_write(jsonObject);
}
