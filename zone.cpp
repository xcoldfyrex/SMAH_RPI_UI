#include "zone.h"

Zone::Zone(int id, char *name, bool hasLedRGB, bool hasLedWhite, bool hasEnviro)
{
    this->id = id;
    this->name = name;
    this-> hasLedRGB = hasLedRGB;
    this->hasLedWhite = hasLedWhite;
    this->hasEnviro = hasEnviro;
}
