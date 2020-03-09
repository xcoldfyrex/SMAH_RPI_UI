#ifndef COMMANDROUTER_H
#define COMMANDROUTER_H

#include "zone.h"
#include "tcpsocket.h"

ClientSocket *determineZone(Light *light);
void broadcastMessage(int srcDevice, int type, float value, int index);
void broadcastMessageJSON(QString type, QJsonObject data);

#endif // COMMANDROUTER_H
