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
    int getActivePreset();
    void setActivePreset(int preset);

private:
    int activePreset;
};

#endif // ZONE_H
