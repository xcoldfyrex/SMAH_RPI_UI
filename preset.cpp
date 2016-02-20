#include "preset.h"

Preset::Preset(QString name, short id, bool dynamic)
{
    this->name = name;
    this->dynamic = dynamic;
    this->id = id;
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

QString Preset::getName() {
    return this->name;
}
