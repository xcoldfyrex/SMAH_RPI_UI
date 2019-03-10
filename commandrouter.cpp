#include "commandrouter.h"
#include "tcpsocket.h"
#include <QDebug>

extern QList<ClientSocket*> g_clientMap;

ClientSocket *determineZone(Light *light)
{
    for (ClientSocket *sock : g_clientMap)
    {
        if (sock->getDeviceID() == light->getGetDeviceId())
        {
            return sock;
        }
    }
    return nullptr;
}

void broadcastMessage(int srcDevice, int type, float value, int index)
{
    for (ClientSocket *sock : g_clientMap)
    {
        QJsonObject jsonPayload;
        jsonPayload["value"] = value;
        jsonPayload["id"] = srcDevice;
        jsonPayload["type"] = type;
        jsonPayload["index"] = index;
        sock->prepareToSend("UPDATE", jsonPayload);
    }
}
