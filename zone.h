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
    virtual ~Zone() {}

    class PowerFunction
    {
    public:
        PowerFunction(int id, QString name);
        int getId() { return this->id; }
        QString getName() { return this->name; }

    protected:
        bool state = false;
        QString name;
        int id;

    private:

    };

    QMap<int, int> environmentMap;
    QMap<int, PowerFunction> powerFunctions;
    QMap<int, QLabel*> *powerStatusLabels;

    QString getName() { return this->name; }
    int getActivePreset() { return this->activePreset; }
    int getId() { return this->id; }
    bool getLedColorCapability() { return this->hasLedRGB; }
    bool getLedWhiteCapability() { return this->hasLedWhite; }
    bool getPowerCapability() { return this->hasPower; }
    bool getEnvironmentCapability() { return this->hasEnviro; }

    void setActivePreset(int preset) { this->activePreset = preset; }

    QPushButton *zoneSelector;
    //static Zone gActiveZone;
    //static QMap<int, Zone*> *gZoneMap;
    ZoneContainerWidget *zoneFunctionContainer;

private:
    int activePreset, id;
    bool hasLedRGB, hasLedWhite, hasEnviro, hasPower;
    QString name;

public slots:
    void sendToNetwork(QString command, QJsonObject jsonPayload);

private slots:
    void updateGPIOLabels(QJsonObject payload, int zoneId);

signals:
    void requestingNetworkOut(QString command, QJsonObject jsonPayload, QString responseTo);
};

#endif // ZONE_H
