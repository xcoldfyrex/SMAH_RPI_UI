#ifndef ZONE_H
#define ZONE_H
#include <QString>
#include <QPushButton>
#include <QMap>

class Zone
{
public:
    Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasPower, bool hasEnviro);
    Zone();
    int id;
    QString name;
    bool hasLedRGB, hasLedWhite, hasEnviro, hasPower;
    int getActivePreset();
    void setActivePreset(int preset);
    QPushButton *zoneSelector;
    static Zone gActiveZone;
    static QMap<int, Zone*> *gZoneMap;
    QMap<int, QList<int>> environmentMap;
    QMap<int, QString> powerToggles;

private:
    int activePreset;

};

#endif // ZONE_H
