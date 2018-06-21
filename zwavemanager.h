#ifndef ZWAVEMANAGER_H
#define ZWAVEMANAGER_H
#include <stdlib.h>

void init_zwave();
void setZWaveToggle(bool value, int nodeid);
bool getZWaveState(int nodeid);

#endif // ZWAVEMANAGER_H
