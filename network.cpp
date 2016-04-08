#include "network.h"

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
    QByteArray Data = socket->readAll();
    qDebug() << "IN" << Data;
    int len = sizeof(Data);
    if (len < 1024)
    {
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

void NetworkThread::socketWrite(QJsonObject data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        QJsonDocument temp(data);
        QString jso(temp.toJson(QJsonDocument::Compact));
        QByteArray ba = jso.toLatin1();
        const char *c_str2 = ba.data();
        char buffer[128];

        sprintf(buffer, "%s", c_str2);
        int slen = strlen(buffer);
        for(; slen < sizeof(buffer)-1;slen++) {
            buffer[slen] = '*';
        }
        buffer[slen] = 0;
        socket->write(buffer);
        qDebug() << strlen(buffer) << "OUT" << buffer;
        socket->flush();
    }
}

void NetworkThread::socketDisconnect() {
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
    socketWrite(payloadStart);
}

void NetworkThread::sendPing()
{
    QJsonObject payloadStart = buildPayload();
    payloadStart["command"] = "PING";
    socketWrite(payloadStart);
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

void NetworkThread::processPayload(QJsonObject data)
{
    QString command = data.value("command").toString();

    if (command == "START" )
    {
        QJsonObject jsonPayload;
        jsonPayload["clientid"] = "100";
        prepareToSend("ID",jsonPayload,data.value("requestID").toString());
    }
}

void NetworkThread::prepareToSend(QString command, QJsonObject jsonPayload, QString responseTo = "") {
    QJsonObject jsonObject = buildPayload();
    jsonObject["command"] = command;
    jsonObject["payload"] = jsonPayload;
    if (responseTo != "") jsonObject["responseTo"] = responseTo;

    socketWrite(jsonObject);
}
