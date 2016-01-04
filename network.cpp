#include "network.h"

NetworkThread::NetworkThread(QString address, quint16 port, QObject *parent)
    : QThread(parent)
{
    this->address = address;
    this->port = port;
}


void NetworkThread::run()
{
    QHostAddress addr(this->address);
    qDebug() << "Conencting to " << addr << this->port;
    socket = new QTcpSocket();
    socket->connectToHost(addr, this->port);
    if (socket->waitForConnected(5000)) {
        sendStart();
    }else {
        qDebug() << "Unable to connect:" << socket->errorString();
        exit(0);
    }
    connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);
    exec();
}

void NetworkThread::sendStart()
{
    QJsonObject payloadStart = buildPayload();
    payloadStart["command"] = "START";
    sendData(payloadStart);
}

void NetworkThread::readyRead()
{
    QByteArray Data = socket->readAll();
    qDebug() << "IN" << Data;
    int len = sizeof(Data);
    if (len < 1024) {
        QString buffer = QString::fromUtf8(Data.data());
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
}

void NetworkThread::sendData(QJsonObject data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        const char *c_str2 = ba.data();
        char buffer[256];
        sprintf(buffer, "%s\n", c_str2);
        socket->write(buffer);
        qDebug() << "OUT" << buffer;
        socket->flush();
    }
    else
    {

    }
}

void NetworkThread::disconnected() {
    qDebug() << socketDescriptor  << "CLOSED" <<  socket->peerAddress().toString();
    //mainWindow.logActivity(mainWindow.txtLog,tr("Lost connection from ").arg(socket->peerAddress().toString()));
    socket->deleteLater();
    exit(0);
}

void NetworkThread::sendPing() {
    QJsonObject payloadStart = buildPayload();
    payloadStart["command"] = "PING";
    sendData(payloadStart);
}

QJsonObject NetworkThread::buildPayload()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long ts =
            (unsigned long long)(tv.tv_sec) * 1000 +
            (unsigned long long)(tv.tv_usec) / 1000;

    char buffer[50];
    sprintf(buffer,"%llx",ts);
    QJsonObject payloadOut;

    payloadOut["requestID"] = QString(buffer);
    return payloadOut;
}

void NetworkThread::processPayload(QJsonObject data) {
    QString command = data.value("command").toString();

    if (command == "START" ) {
        QJsonObject payloadObject;
        QJsonObject payloadStart = buildPayload();
        payloadStart["responseTo"] = data.value("requestID").toString();
        payloadStart["command"] = "ID";
        payloadObject["clientid"] = "100";
        payloadStart["payload"] = payloadObject;
        sendData(payloadStart);
    }
}
