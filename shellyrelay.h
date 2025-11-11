#ifndef SHELLYRELAY_H
#define SHELLYRELAY_H

#include "shelly.h"

class ShellyRelay : public Shelly
{
public:
    explicit ShellyRelay(QString ip, QString mDNS, QObject *parent);
};

#endif // SHELLYRELAY_H
