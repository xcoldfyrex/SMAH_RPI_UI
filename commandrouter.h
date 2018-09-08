#ifndef COMMANDROUTER_H
#define COMMANDROUTER_H

#include "zone.h"
#include "tcpsocket.h"

ClientSocket *determineZone(Light *light);
void broadcastMessage(int srcDevice, int value);

#endif // COMMANDROUTER_H
