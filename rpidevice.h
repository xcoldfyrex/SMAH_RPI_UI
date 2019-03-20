#ifndef LIBSMAHDEVICE_H
#define LIBSMAHDEVICE_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QList>
#include <QtDebug>

class RPIDevice : public QObject
{
    Q_OBJECT

    class LightFunction;
    class EnvironmentFunction;
    class PowerFunction;

public:
    explicit RPIDevice(QObject *parent = nullptr);
    RPIDevice(int id, QString name, QString hwAddress);
    int getId() const { return this->id; }
    QString getName() const { return this->name; }
    QString getHwAddress() const { return this->hwAddress; }
    QMap<int, PowerFunction> getPowerFunctionList() const { return this->powerControls; }
    long getConnectionStart() { return this->connectTime; }
    int getVersion() { return this->version; }
    QString getName() { return this->name; }
    QString getIP() { return this->ip; }
    QString ip = "not connected";
    void setIP(QString ipa) {
        ip = ipa;
        emit ipChanged(ipa);
    }
    void setVersion(int v) { this->version = v; }
    void setConnectionStart(long t) { this->connectTime = t; }


private:
    int id;
    int version;
    QString name, hwAddress;
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

signals:
    void ipChanged(QString ip);

};


#endif // LIBSMAHDEVICE_H
