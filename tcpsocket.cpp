#include "tcpsocket.h"
#include "zone.h"
#include "build_number.h"
#include "tcpconnectionfactory.h"

#include <QNetworkInterface>
#include <QJsonObject>

extern QList<ClientSocket*> g_clientMap;
extern QMap<QString, Zone*> gZoneMap;
extern QMap<QString, RPIDevice*> g_deviceList;
extern QList <Sensor*> g_sensorList;
extern QMap<int, Light*> g_lightMap;
extern QMap<int, Preset*> gColorPresetMap;
extern QString MY_HW_ADDR;

extern TCPConnectionFactory tcpServer;


void ClientSocket::stateChanged(QAbstractSocket::SocketState socketState){
    qInfo() << socketState;
}

// spawned by the tcpserver
ClientSocket::ClientSocket(QTcpSocket *ID, QObject *parent)
    : QObject(parent)
{
    this->blockSize = 0;

    this->tcpSocket = ID;

    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()));


    peer_address = this->tcpSocket->peerAddress().toString().toStdString();
    this->remoteAddress = this->tcpSocket->peerAddress();
    this->parent = parent;
    tcpSocket->waitForConnected(10000);
    connect(tcpSocket, &QAbstractSocket::connected,[this]()
    {
        qDebug() << "SENDING INBOUND" << this->tcpSocket->peerAddress().toString();
        QJsonObject data;
    });
    //connect(&tcpServer, SIGNAL(broadcastSignal(QString, QJsonObject)), this, SLOT(prepareToSend(QString,QJsonObject)));


}

// we conencted as a client
ClientSocket::ClientSocket(QHostAddress address, QObject *parent)
    : QObject(parent)
{
    this->blockSize = 0;
    this->tcpSocket = new QTcpSocket();
    this->remoteAddress = address;
    connect(tcpSocket, SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(tcpSocket, SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

    tcpSocket->close();
    connect(tcpSocket, &QAbstractSocket::connected,[this]()
    {
        // qDebug() << "SENDING OUTBOUND" << this->tcpSocket->peerAddress().toString();
        QJsonObject data;
    });

    tcpSocket->connectToHost(address,9002);
    tcpSocket->waitForConnected(10000);
    //connect(&tcpServer, SIGNAL(broadcastSignal(QString, QJsonObject)), this, SLOT(prepareToSend(QString,QJsonObject)));
}

void ClientSocket::sendData(QJsonObject data)
{
    if (tcpSocket == nullptr)
    {
        qWarning() << "Tried to send on null socket: " << data;
        return;
    }

    if(tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_0);
        out << static_cast<quint16>(0);
        out << ba;
        out.device()->seek(0);
        out << static_cast<quint16>(static_cast<unsigned long>(block.size()) - sizeof(quint16));
        tcpSocket->write(block);
        tcpSocket->waitForBytesWritten(5000);
        tcpSocket->flush();

        // qDebug() << data;

    //} else if (tcpSocket->state() == QAbstractSocket::cl) {

    } else if (tcpSocket->state() == QAbstractSocket::ConnectingState) {
        qDebug() << "DID NOT CONNECT YET" << tcpSocket->state() << this->remoteAddress << data;
    } else  {
        qDebug() << "BAD STATE" << tcpSocket->state() << this->remoteAddress << data;
        g_clientMap.removeOne(this);
        //tcpSocket->deleteLater();
        //tcpSocket->close();
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

        if (tcpSocket->bytesAvailable() < static_cast<int>(blockSize))
            return;

        in >> buffer;
        processPayload(buffer);
        blockSize = 0;
    }
}

void ClientSocket::disconnected() {
    //qInfo("Client disconnect(%s)", tcpSocket->peerAddress().toString().toStdString().c_str());
    if (g_deviceList.contains(this->devid))
    {
        qDebug() << "CLOSED ClientSocket " << this->getPeerAddress();
        qInfo() << "Device LEFT: " << this->rpidevice->getHwAddress() << this->rpidevice->getName() << tcpSocket->errorString().toStdString().c_str();
        this->rpidevice->setVersion(0);
        this->rpidevice->setIP("-");
    }
    g_clientMap.removeOne(this);
    tcpSocket->close();
    tcpSocket->deleteLater();
}

void ClientSocket::socketError()
{
    qWarning() << "Socket error on host:"  << this->remoteAddress.toString() << tcpSocket->errorString().toStdString().c_str();
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
//void ClientSocket::prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo)
//{
//    QJsonObject jsonObject = buildPayload();
//    jsonObject["command"] = command;
//    jsonObject["payload"] = jsonPayload;
//    if (responseTo != "")
//        jsonObject["responseTo"] = responseTo;
//
//    sendData(jsonObject);
//}

/* overloaded, maybe just keep this */
//void ClientSocket::prepareToSend(QString command, QJsonObject jsonPayload)
//{
//    QJsonObject jsonObject = buildPayload();
//    jsonObject["command"] = command;
//    jsonObject["payload"] = jsonPayload;
//    sendData(jsonObject);
//}


void ClientSocket::processPayload(QByteArray buffer){
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

}
