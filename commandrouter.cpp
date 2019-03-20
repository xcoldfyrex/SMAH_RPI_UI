#include "commandrouter.h"
#include <QDebug>

extern QList<ClientSocket*> g_clientMap;

ClientSocket *determineZone(Light *light)
{
    for (ClientSocket *sock : g_clientMap)
    {
        if (sock->getRPIDeviceID() == light->getGetDeviceId())
        {
            return sock;
        }
    }
    return nullptr;
}
