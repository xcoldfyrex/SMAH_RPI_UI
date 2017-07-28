#ifndef ZONE_H
#define ZONE_H
#include <QString>
#include <QPushButton>
#include <QMap>
#include <QLabel>
#include <QObject>

#include "w_zonecontainer.h"

class ZoneContainerWidget;

class Zone : public QObject
{
    Q_OBJECT
public:
    Zone(int id, QString name, bool hasLedRGB, bool hasLedWhite, bool hasPower, bool hasEnviro, QObject *parent);
    Zone();
    virtual ~Zone() {}

    class PowerFunction
    {
    public:
        PowerFunction(int id, QString name);
        PowerFunction();
        bool state = false;
        QString name;
        int id;
    private:

    };

    QMap<int, PowerFunction> powerFunctions;
    int id;
    QString name;
    bool hasLedRGB, hasLedWhite, hasEnviro, hasPower;
    int getActivePreset();
    void setActivePreset(int preset);
    QPushButton *zoneSelector;
    static Zone gActiveZone;
    static QMap<int, Zone*> *gZoneMap;
    QMap<int, int> environmentMap;
    ZoneContainerWidget *zoneFunctionContainer;
    QMap<int, QLabel*> *powerStatusLabels;

private:
    int activePreset;

private slots:
    void updateGPIOLabels(QJsonObject payload, int zoneId);

};

#endif // ZONE_H
