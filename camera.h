#ifndef CAMERA_H
#define CAMERA_H

#include <QString>

class Camera
{
public:
    Camera(QString name, QString low, QString med, QString high);

private:
    typedef struct mSettings
    {
        QString name = "";
        QString low = "";
        QString med = "";
        QString high = "";
    } mSettings;

    QString name = "";
    QString low = "";
    QString med = "";
    QString high = "";

public:
    mSettings getSettings() {
        mSettings settings;
        settings.name = name;
        settings.low = low;
        settings.med = med;
        settings.high = high;
        return settings;
    }
};


#endif // CAMERA_H
