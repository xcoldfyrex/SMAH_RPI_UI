#ifndef ZONE_H
#define ZONE_H


class zone
{
public:
    zone(int id, char *name, bool hasLedRGB, bool hasLedWhite, bool hasEnviro);
    int id;
    char *name;
    bool hasLedRGB, hasLedWhite, hasEnviro;
};

#endif // ZONE_H
