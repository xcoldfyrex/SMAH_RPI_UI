#include "zone.h"

Zone::Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasPower, bool hasEnviro)
{
    this->id = id;
    this->name = name;
    this->hasLedRGB = hasLedRGB;
    this->hasLedWhite = hasLedWhite;
    this->hasEnviro = hasEnviro;
    this->hasPower = hasPower;
    zoneSelector = new QPushButton(this->name);
    zoneFunctionContainer = new ZoneContainerWidget(this);
}

Zone::Zone()
{
    this->hasEnviro = false;
}

int Zone::getActivePreset() {
    return this->activePreset;
}

void Zone::setActivePreset(int preset) {
    this->activePreset = preset;
}
