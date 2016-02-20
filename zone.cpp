#include "zone.h"

Zone::Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasEnviro)
{
    this->id = id;
    this->name = name;
    this-> hasLedRGB = hasLedRGB;
    this->hasLedWhite = hasLedWhite;
    this->hasEnviro = hasEnviro;
}

Zone::Zone()
{

}

int Zone::getActivePreset() {
    return this->activePreset;
}

void Zone::setActivePreset(int preset) {
    this->activePreset = preset;
}
