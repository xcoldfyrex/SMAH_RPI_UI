#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "qdom.h"
#include <QObject>
#include <QVariant>

class Configuration  : public QObject
{
    Q_OBJECT

public:
    Configuration();
    /* non zone members */
    Q_PROPERTY(QVariantList getAmbientLoopConfigurations READ getAmbientLoopConfigurations CONSTANT)
    struct AmbientLoopConfiguration {
        QString mName = "foo";
        QString mFile = "bar";
        QVariantMap toMap() {
            return {
                { "mName", mName },
                { "mFile", mFile }
            };
        }
    };

    struct ShellyConfiguration {
        QString mID;
        QString mIP;
    };

    struct CameraConfiguration {
        QString mName;
        QString mLowRTSP;
        QString mMedRTSP;
        QString mHighRTSP;
    };

    struct PresetConfiguration {
        QString mName;
        QString mColorCode;
    };

    struct SceneItemConfiguration {
        bool mState;
        QString mDevice;
        QString mColorCode;
    };

    struct SceneGroupConfiguration {
        QString mName;
        QList<QString> mZones;
        QList<SceneItemConfiguration> mSceneItems;
    };

    /* zone members */
    struct LightConfiguration {
        QString mName;
        QString mShellyID;
    };

    struct SensorConfiguration {
        QString mName;
        QString mID;
    };

    struct ZoneConfiguration {
        QString mName;
        QString mColorCode;
        QList<Configuration::LightConfiguration> mLightConfigurations;
        QList<Configuration::SensorConfiguration> mSensorConfigurations;
    };

    /* base config object */
    struct Config
    {
        QList<Configuration::ZoneConfiguration> mZoneConfigurations;
        QList<Configuration::ShellyConfiguration> mShellyConfigurations;
        QList<Configuration::CameraConfiguration> mCameraConfigurations;
        QList<Configuration::PresetConfiguration> mPresetConfigurations;
        QList<Configuration::SceneGroupConfiguration> mSceneGroupConfigurations;
        QList<Configuration::AmbientLoopConfiguration> mAmbientLoopConfigurations;
    };

    Q_INVOKABLE Config getConfiguration() { return this->config; };
    QVariantList getAmbientLoopConfigurations() {
        QVariantList l;
        for (Configuration::AmbientLoopConfiguration &c : this->config.mAmbientLoopConfigurations) {
            l.append(c.toMap());
        }
        return l;
    };
    Q_INVOKABLE bool loadBaseConfiguration();
    Q_INVOKABLE bool loadUserDefinedConfiguration();


private:
    Config config;
    QDomDocument validateConfigFile(QString config);

};


#endif // CONFIGURATION_H
