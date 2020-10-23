#ifndef ZWAVEWORKER_H
#define ZWAVEWORKER_H

#include <QObject>
#include <QThread>
#include <QFileInfo>
#include <QDebug>

#include <zwavemanager.h>

class ZWaveWorker : public QThread
{
    Q_OBJECT
public:
    explicit ZWaveWorker(QObject &parent);
    void run() override {
        if (QFileInfo::exists("/dev/ttyACM0"))
        {
            qInfo() << "INIT ZWave";
            init_zwave();
            qInfo() << "ZWave Polling Complete";
        } else {
            qInfo() << "ZWave device not found. Skipping.";
        }
    }

signals:

public slots:
};

#endif // ZWAVEWORKER_H
