#include "preset.h"

Preset::Preset(QString name, bool dynamic)
{
    this->name = name;
    this->dynamic = dynamic;
}

QMap<int,Preset::Step> Preset::getSteps() {
    return this->stepMap;
}

void Preset::setColor(QString color) {
    this->r = color.mid(1,1).toShort();
    this->g = color.mid(3,1).toShort();
    this->b = color.mid(5,1).toShort();
    this->w = color.mid(7,1).toShort();
}
