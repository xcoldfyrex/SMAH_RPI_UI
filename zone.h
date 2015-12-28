#ifndef ZONE_H
#define ZONE_H
#include <QString>

class Zone
{
public:
    Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasEnviro);
    Zone();
    int id;
    QString name;
    bool hasLedRGB, hasLedWhite, hasEnviro;
};

#endif // ZONE_H
