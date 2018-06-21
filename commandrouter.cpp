#include "commandrouter.h"
#include "tcpsocket.h"
#include <QDebug>

extern QList<ClientSocket*> g_clientMap;


ClientSocket *determineZone(Light *light)
{
    for (ClientSocket *sock : g_clientMap)
    {
        if (sock->getDevice().getId() == light->getGetDeviceId())
        {
            return sock;
        }
    }
    return NULL;
}
