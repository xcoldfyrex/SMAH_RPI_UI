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

private:
    int id;
    QString name, hwAddress;
    QMap <int, PowerFunction> powerControls;
    QMap <int, EnvironmentFunction> enviroData;
    QMap <int, LightFunction> lightControls;

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
        QString getName() { return this->name; }

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
