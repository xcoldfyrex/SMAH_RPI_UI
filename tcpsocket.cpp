#include "tcpsocket.h"
#include "zone.h"
#include <QNetworkInterface>

extern QList<ClientSocket*> g_clientMap;
extern QMap <QString, RPIDevice> g_deviceList;
extern QMap <int, Light*> g_lightMap;
extern QMap<int, Preset> gColorPresetMap;


// spawned by the tcpserver
ClientSocket::ClientSocket(qintptr ID, QObject *parent)
    : QObject(parent)
{
    this->socketDescriptor = ID;
    this->blockSize = 0;

    tcpSocket = new QTcpSocket();

    if (!tcpSocket->setSocketDescriptor(this->socketDescriptor)) {
        emit error(tcpSocket->error());
        return;
    }
    else
    {
        pingTimer = new QTimer();
        pingTimer->setInterval(60000);
        pingTimer->start();
    }

    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));
    peer_address = this->tcpSocket->peerAddress().toString().toStdString();
    this->remoteAddress = this->tcpSocket->peerAddress();
    this->parent = parent;
    QJsonObject data;
    send_id(this->tcpSocket, data);
}

// we conencted as a client
ClientSocket::ClientSocket(QHostAddress address, QObject *parent)
    : QObject(parent)
{
    this->blockSize = 0;
    this->tcpSocket = new QTcpSocket();
    this->remoteAddress = address;
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    tcpSocket->close();
    tcpSocket->connectToHost(address,9002);
    QJsonObject data;
    send_id(this->tcpSocket,data);
}

void ClientSocket::sendData(QJsonObject data)
{
    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_0);
        out << (quint16)0;
        out << ba;
        out.device()->seek(0);
        out << (quint16)(block.size() - sizeof(quint16));
        tcpSocket->write(block);
        tcpSocket->flush();
    }
}

void ClientSocket::readyRead()
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
        processPayload(buffer);
        blockSize = 0;
    }
}

void ClientSocket::disconnected() {
    qInfo("Client disconnect(%s)", tcpSocket->peerAddress().toString().toStdString().c_str());
    tcpSocket->deleteLater();
}

void ClientSocket::socketError()
{
    qWarning() << "Socket error on host:"  << this->remoteAddress.toString() << tcpSocket->errorString().toStdString().c_str();
    g_clientMap.removeOne(this);
    tcpSocket->deleteLater();
}

/* generates a JSON object to encapsulate payload */
QJsonObject ClientSocket::buildPayload()
{
    char buffer[12];
    for(int i = 0; i < 11; i++) {
        sprintf(buffer + i, "%x", rand() % 16);
    }
    QJsonObject payloadOut;

    payloadOut["requestID"] = QString(buffer);
    return payloadOut;
}

/* prepares the entire payload and sends to socket */
void ClientSocket::prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo)
{
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = command;
    jsonObject["payload"] = jsonPayload;
    if (responseTo != "")
        jsonObject["responseTo"] = responseTo;

    sendData(jsonObject);
}

/* overloaded, maybe just keep this */
void ClientSocket::prepareToSend(QString command, QJsonObject jsonPayload)
{
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = command;
    jsonObject["payload"] = jsonPayload;
    sendData(jsonObject);
}

/* does all shit needed to send the proper ID to server*/
void ClientSocket::send_id(QTcpSocket *tcpSocket, QJsonObject data)
{
    QString mac = "N/A";
    //QNetworkInterface interface = QNetworkInterface::interfaceFromName(QString("wlp36s0"));
    //mac = interface.hardwareAddress();
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
            foreach (QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (interface.name() == "wlp36s0" || interface.name() == "wlan0")
                {
                    mac = interface.hardwareAddress();
                    break;
                }
            }

    }
    QJsonObject jsonPayload;
    jsonPayload["clientid"] = mac;
    prepareToSend("ID", jsonPayload, data.value("requestID").toString());
}

void ClientSocket::processPayload(QByteArray buffer)
{
    qDebug() << buffer;
    QJsonDocument doc = QJsonDocument::fromJson(buffer.data());
    if(doc.isNull())
    {
        qWarning() << socketDescriptor << "ERROR Invalid JSON...";
        return;
    }

    QJsonObject data = doc.object();
    QString command = data.value("command").toString();
    QString resource = data.value("resource").toString();
    QString requestID = data.value("requestID").toString();
    QString responseTo = data.value("responseTo").toString();

    QJsonObject incomingPayload = data.value("payload").toObject();

    /* general payload for shit outgoing */
    QJsonObject outgoingData = buildPayload();
    outgoingData["responseTo"] = data.value("requestID").toString();

    /* Client starts authentication */
    if (command == "ID" )
    {
        QString devid = incomingPayload["clientid"].toString();
        if (g_deviceList.contains(devid))
        {
            this->rpidevice = g_deviceList.value(devid);
            qInfo() << "Device connected: " << this->rpidevice.getHwAddress() << this->rpidevice.getName();
        } else {
            qWarning() << "Unknown device connected: " << devid;
        }
        /* send values of local lights */
        for (Light *light : g_lightMap.values())
        {
            if (light->wasLastUpdateLocal())
            {
                light->sendUpdate();
            }
        }
    }

    /* light color change (gpio) */
    if (command == "RGBW" )
    {
        QString value = incomingPayload["value"].toString();
        int id = incomingPayload["id"].toInt();

        if (g_lightMap.contains(id))
        {
            g_lightMap.value(id)->setColorInPWM(value);
        }
    }

    /* flip zwave state */
    if (command == "TOGGLE" )
    {
        int id = incomingPayload["id"].toInt();
        if (g_lightMap.contains(id))
        {
            g_lightMap.value(id)->toggleState();
        }
    }

    /* preset toggle */
    if (command == "PRESET" )
    {
        int value = incomingPayload["value"].toInt();
        int id = incomingPayload["id"].toInt();

        if (g_lightMap.contains(id))
        {
            if (gColorPresetMap.contains(value))
                g_lightMap.value(id)->setActivePreset(gColorPresetMap.value(value));
        }
    }

    /* preset toggle */
    if (command == "UPDATE" )
    {
        int value = incomingPayload["value"].toInt();
        int id = incomingPayload["id"].toInt();

        if (g_lightMap.contains(id))
        {
                g_lightMap.value(id)->setLastUpdateLocal(false);
                g_lightMap.value(id)->updateLevel(value);
        }
    }
}
