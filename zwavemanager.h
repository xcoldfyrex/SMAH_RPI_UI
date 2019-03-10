#ifndef ZWAVEMANAGER_H
#define ZWAVEMANAGER_H
#include <stdlib.h>
#include "value_classes/Value.h"

void init_zwave();
void setZWaveToggle(bool value, int nodeid);
void setZWaveLevel(uint8 value, int nodeid);
bool getZWaveState(int nodeid);

#endif // ZWAVEMANAGER_H
