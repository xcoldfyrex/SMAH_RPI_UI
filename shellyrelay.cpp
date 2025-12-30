#include "shellyrelay.h"

ShellyRelay::ShellyRelay(QString ip, QString mDNS, QString type, QObject *parent)
    : Shelly{ip,  mDNS, type, parent}
{
    this->ip = ip;
    this->mDNS = mDNS;
}
