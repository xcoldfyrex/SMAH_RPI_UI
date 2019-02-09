#ifndef LIBSMAHDEVICE_H
#define LIBSMAHDEVICE_H

#include <QString>
#include <QMap>
#include <QList>

class RPIDevice
{
    class LightFunction;
    class EnvironmentFunction;
    class PowerFunction;

public:
    RPIDevice(int id, QString name, QString hwAddress);
    RPIDevice();
    int getId() const { return this->id; }
    QString getName() const { return this->name; }
    QString getHwAddress() const { return this->hwAddress; }
    QMap<int, PowerFunction> getPowerFunctionList() const { return this->powerControls; }
    long getConnectionStart() { return this->connectTime; }
    QString getName() { return this->name; }
    QString getIP() { return this->ip; }
    void setIP(QString ip) {  this->ip = ip; }
    void setConnectionStart(long t) { this->connectTime = t; }

private:
    int id;
    QString name, hwAddress, ip;
    QMap <int, PowerFunction> powerControls;
    QMap <int, EnvironmentFunction> enviroData;
    QMap <int, LightFunction> lightControls;    
    long connectTime;

    class LightFunction {
        QString name;
        short type;
        int id;
    };

    class PowerFunction
    {
    public:
        PowerFunction(QString name, int id, short type);
        int getId() { return this->id; }
        int getType() { return this->type; }

    protected:
        bool state = false;
        QString name;
        int id;
        short type;


    private:

    };

    class EnvironmentFunction {
        QString name;
        short type;
        int id;
    };

};


#endif // LIBSMAHDEVICE_H
