#include "network.h"

extern QList<Zone*> *gZoneList;

NetworkThread::NetworkThread(QString address, quint16 port, QObject *parent)
    : QThread(parent)
{
    this->address = address;
    this->port = port;
}

NetworkThread::NetworkThread() {

}

void NetworkThread::run()
{
    socket = new QTcpSocket();
    //connect(socket, SIGNAL(connected()), this, SLOT(socketConnect()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError()),Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()),this,SLOT(socketRead()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()),this,SLOT(socketDisconnect()),Qt::DirectConnection);
    errcnt = 0;
    socketConnect();

    exec();
}

void NetworkThread::socketConnect()
{
    QHostAddress addr(this->address);
    qDebug() << "Conencting to " << addr << this->port;
    socket->connectToHost(addr, this->port);
    if (socket->waitForConnected(5000))
    {
        sendStart();
    }
}

void NetworkThread::socketRead()
{

    QByteArray stream;
    QByteArray data = "";
    while (socket->bytesAvailable() && !data.contains('\n')) {
        QByteArray data = socket->read(1);
        stream.append(data);

    }
    qDebug() << "IN" << stream;

    QString buffer = QString::fromUtf8(stream.data());
    QJsonDocument doc = QJsonDocument::fromJson(buffer.toUtf8());
    if(!doc.isNull())
    {
        if(doc.isObject())
        {
            processPayload(doc.object());
        }
        else
        {
            qDebug() << socketDescriptor << "ERROR Document is not an object" << endl;
        }
    }
    else
    {
        qDebug() << socketDescriptor << "ERROR Invalid JSON...\n" << buffer << endl;
    }

}

void NetworkThread::socket_write(QJsonObject data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        const char *c_str2 = ba.data();
        char buffer[128];
        sprintf(buffer, "%s\n", c_str2);

        socket->write(buffer);
        qDebug() << strlen(buffer) << "OUT" << buffer;
        socket->flush();
    }
}

void NetworkThread::socketDisconnect()
{
    qDebug() << socketDescriptor  << "CLOSED" <<  socket->peerAddress().toString();
    //mainWindow.logActivity(mainWindow.txtLog,tr("Lost connection from ").arg(socket->peerAddress().toString()));
}

void NetworkThread::socketError()
{
    if (errcnt >= 4096)
    {
        qDebug() << "Unable able to connect after " << errcnt << "tries, giving up";
        socket->deleteLater();
        this->exit(1);
        return;
    }
    errcnt++;
    qDebug() << "Socket error:" << errcnt << socket->errorString();
    socket->abort();
    this->sleep(1);
    socketConnect();
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

void NetworkThread::processPayload(QJsonObject data)
{
    QString command = data.value("command").toString();

    //start negotiation
    if (command == "START" )
    {
        QJsonObject jsonPayload;
        jsonPayload["clientid"] = "100";
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
                foreach (const QJsonValue & value, array)
                {
                    QJsonObject obj = value.toObject();
                    Zone *zone = new Zone(obj["id"].toInt(), obj["name"].toString(), true, true, true);
                    gZoneList->append(zone);
                    emit zoneArrived(zone);
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
