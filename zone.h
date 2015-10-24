#ifndef ZONE_H
#define ZONE_H
#include <QString>

class Zone
{
public:
    Zone(int id, char *name, bool hasLedRGB, bool hasLedWhite, bool hasEnviro);
    int id;
    QString name;
    bool hasLedRGB, hasLedWhite, hasEnviro;
};

#endif // ZONE_H
