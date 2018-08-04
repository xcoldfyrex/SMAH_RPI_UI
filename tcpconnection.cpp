#include "tcpconnection.h"
//#include "libsmah_network.h"
#include "zone2.h"

//extern QMap<QString, smah::Zone> gZoneMap;
//QMap<int, Zone*> *gZoneMapDELETEME;

QByteArray socketBuffer;

TCPConnection::TCPConnection(QObject *parent)
    : QObject(parent)
{
    this->address = address;
    this->port = 9002;
    this->blockSize = 0;
    this->tcpSocket = new QTcpSocket();
    reconnectTimer = new QTimer();
    reconnectTimer->setInterval(5000);

    enviroTimer = new QTimer();
    enviroTimer->setInterval(1000);

    //connect(reconnectTimer, SIGNAL(timeout()), this, SLOT(socketConnect()),Qt::DirectConnection);
    connect(enviroTimer, SIGNAL(timeout()), this, SLOT(GPIOPoll()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(socketRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(socketDisconnect()),Qt::DirectConnection);
    errcnt = 0;
}

TCPConnection::TCPConnection() {

}

void TCPConnection::start(QHostAddress address)
{
    socketConnect(address);
}

void TCPConnection::socketConnect(QHostAddress addr)
{
    tcpSocket->close();
    tcpSocket->connectToHost(addr,9002);
    if (tcpSocket->waitForConnected(5000))
    {
        reconnectTimer->stop();
    }
}

void TCPConnection::socketRead()
{
    QDataStream in(tcpSocket);
    QByteArray buffer;
    in.setVersion(QDataStream::Qt_5_0);

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
        qDebug() << "IN" << blockSize << QString(buffer);
        processPayload(buffer, in);
        blockSize = 0;
    }
}


void TCPConnection::socketDisconnect()
{
    qDebug() << socketDescriptor  << "CLOSED" <<  tcpSocket->peerAddress().toString();
}

void TCPConnection::socketError()
{
    qWarning() << "Socket error:" << tcpSocket->errorString().toStdString().c_str();
    if (!reconnectTimer->isActive())
    {
        reconnectTimer->start();
        enviroTimer->stop();
    }
}

QJsonObject TCPConnection::makeJsonObject(QByteArray buffer)
{
    if (buffer.length() == 0)
        QJsonDocument().object();

    QJsonDocument doc = QJsonDocument::fromJson(buffer.data());
    if(doc.isNull())
    {
        qDebug() << socketDescriptor << "ERROR Invalid JSON..." << buffer;
        return QJsonDocument().object();
    }

    return doc.object();
}
void TCPConnection::processPayload(QByteArray &buffer, QDataStream &payload)
{
    qDebug() << "BYTES TOP" << payload.device()->bytesAvailable();

    QJsonObject data = makeJsonObject(buffer);
    QString command = data.value("command").toString();

    // zone(s) and the properties are sent
    if (command == "ZONE_UPDATE" )
    {
        /*
        quint16 count;
        payload >> count;
        const quint16 counter = count;

        for(quint16 a = 0; a < counter; ++a)
        {
            smah::Zone zone;
            payload >> zone;
            if (!gZoneMap.contains(zone.getName())) {
                gZoneMap.insert(zone.getName(),zone);
                qDebug() << zone.getName();
                emit zoneDiscovered(zone);
            }
        }
        */
    }

    //

    //server responded to a GET_RESOURCE or GET
    if (command == "RESPOND" )
    {
        QString id = data.value("responseTo").toString();
        int zone = data.value("zone").toInt();

        if (outstanding.contains(id))
        {
            QString type = outstanding.value(id);


            if (type == "GPIO")
            {
                QJsonObject payload = data.value("payload").toObject();
                emit zoneGPIOArrived(payload, zone);
            }

            if (type == "ACTIONS")
            {
                /*
                QJsonArray array = data.value("payload").toArray();
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    int id = obj["id"].toInt();
                    ScheduledAction action = new Preset(obj["name"].toString(),presetID);
                    emit presetArrived(preset);
                }
                */
            }
            outstanding.remove(id);
        }

    }

    return;
}


void TCPConnection::enviroPoll()
{
    /*
    foreach (Zone *zone, *gZoneMap) {
        if (zone->getEnvironmentCapability()) {
            QJsonObject jsonObject = smah::buildPayload();
            jsonObject["command"] = "GET";
            jsonObject["resource"] = "MCP320X";
            jsonObject["zone"] = zone->getId();

            outstanding.insert(jsonObject["requestID"].toString(), "MCP320X");
            smah::socket_write(jsonObject, tcpSocket);
        }
    }
    */
}

void TCPConnection::GPIOPoll()
{
    /*
    foreach (Zone *zone, *gZoneMap) {
            QJsonObject jsonObject = smah::buildPayload();
            jsonObject["command"] = "GET";
            jsonObject["resource"] = "GPIO";
            jsonObject["zone"] = zone->getId();

            outstanding.insert(jsonObject["requestID"].toString(), "GPIO");
            smah::socket_write(jsonObject, tcpSocket);
        }
    */
}

QString TCPConnection::getIp_addr()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
     for(int nIter=0; nIter<list.count(); nIter++)

      {
          if(!list[nIter].isLoopback())
              if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
            return list[nIter].toString();
      }
}

QString TCPConnection::getMAC_addr()
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (interface.name() == "wlp36s0" || interface.name() == "wlan0")
                {
                    return interface.hardwareAddress();

                }
            }
    }
}
