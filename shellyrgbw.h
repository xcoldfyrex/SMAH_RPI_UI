#ifndef SHELLYRGBW_H
#define SHELLYRGBW_H

#include "shelly.h"

class ShellyRGBW : public Shelly
{
public:
    explicit ShellyRGBW(QString ip, QString mDNS, QObject *parent = nullptr);

    void setRGBW(int r, int g, int b, int w);
    void setRGBW(QString color);
    void setValue(QString type, QString val, bool on);
};

#endif // SHELLYRGBW_H
