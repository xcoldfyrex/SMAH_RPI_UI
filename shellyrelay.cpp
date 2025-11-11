#include "shellyrelay.h"

ShellyRelay::ShellyRelay(QString ip, QString mDNS, QObject *parent)
    : Shelly{ip,  mDNS,  parent}
{
    this->ip = ip;
    this->mDNS = mDNS;
}
