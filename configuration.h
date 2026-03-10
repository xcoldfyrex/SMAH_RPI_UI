#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "configurationwriter.h"
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

    struct ActionItemConfiguration {
        QString mElementName = "action";
        QString mType;
        QString mAction = "SHELLY_ON";
        QVariant mValue = 0;
        QString mTime = "00:00";
        int mRepeat = 0;
        int mInterval = 0;
        QVariantMap toMap() {
            return {
                    { "mType", mType },
                    { "mAction", mAction },
                    { "mValue", mValue },
                    { "mTime", mTime },
                    { "mRepeat", mRepeat },
                    { "mInterval", mInterval },
                    { "mElementName", mElementName },
                    };
        }
    };

    struct ActionGroupConfiguration {
        QString mName;
        QString mElementName = "action";
        QList<ActionItemConfiguration> mActionItems;
        QList<QString> mShellyID;
        QVariantMap toMap() {
            QVariantList l;
            for (Configuration::ActionItemConfiguration &c : mActionItems) {
                l.append(c.toMap());
            }
            return {
                { "mName", mName },
                { "mElementName", mElementName },
                { "mShellyID", mShellyID },
                { "mElements", l}
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
        QVariantMap toMap() {
            return {
                { "mName", mName },
                { "mLowRTSP", mLowRTSP },
                { "mMedRTSP", mMedRTSP },
                { "mHighRTSP", mHighRTSP }
            };
        }
    };

    struct PresetConfiguration {
        QString mName;
        QString mColorCode;
    };

    struct SceneItemConfiguration {
        bool mState;
        QString mDevice;
        QString mColorCode;
        QString mElementName = "item";
        QVariantMap toMap() {
            return {
                { "mDevice", mDevice },
                { "mState", mState },
                { "mColorCode", mColorCode },
                { "mElementName", mElementName }
            };
        }
    };

    struct SceneGroupConfiguration {
        QString mName;
        QString mElementName = "scene";
        QList<QString> mZones;
        QList<SceneItemConfiguration> mSceneItems;
        QVariantMap toMap() {
            QVariantList l;
            for (Configuration::SceneItemConfiguration &c : mSceneItems) {
                l.append(c.toMap());
            }
            return {
                { "mName", mName },
                { "mElementName", mElementName },
                { "mElements", l}
            };
        }

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
        QList<Configuration::ActionGroupConfiguration> mActionGroupConfigurations;
    };

    /* return a generic config object for QML */
    Q_INVOKABLE Config getConfiguration() { return this->config; };

    /* intented to be used by XML writer */
    Q_INVOKABLE QVariantList getActionConfigurationAsMap() {
        QVariantList m;
        for (Configuration::ActionGroupConfiguration &c : this->config.mActionGroupConfigurations) {
            m.append(c.toMap());
        }
        return m;
    };

    /* intented to be used by XML writer */
    Q_INVOKABLE QVariantList getSceneConfigurationAsMap() {
        QVariantList m;
        for (Configuration::SceneGroupConfiguration &c : this->config.mSceneGroupConfigurations) {
            m.append(c.toMap());
        }
        return m;
    };

    QVariantList getAmbientLoopConfigurations() {
        QVariantList l;
        for (Configuration::AmbientLoopConfiguration &c : this->config.mAmbientLoopConfigurations) {
            l.append(c.toMap());
        }
        return l;
    };

    Q_INVOKABLE QVariantList getCameraConfigurations() {
        QVariantList l;
        for (Configuration::CameraConfiguration &c : this->config.mCameraConfigurations) {
            l.append(c.toMap());
        }
        return l;
    };

    Q_INVOKABLE QVariantList getActionItemConfigurations(int index) {
        QVariantList l;
        for (Configuration::ActionItemConfiguration &c : this->config.mActionGroupConfigurations[index].mActionItems) {
            l.append(c.toMap());
        }
        return l;
    };

    Q_INVOKABLE bool loadBaseConfiguration();
    Q_INVOKABLE bool loadUserDefinedConfiguration();

    Q_INVOKABLE void addActionItemConfigurations(int index) {
        Configuration::ActionItemConfiguration action;
        config.mActionGroupConfigurations[index].mActionItems.append(action);
    };

    Q_INVOKABLE void delActionItemConfigurations(int index, int itemIndex) {
        if (config.mActionGroupConfigurations[index].mActionItems.length() == 0) {
            qWarning() << "Tried remove element from empty list";
        } else {
            config.mActionGroupConfigurations[index].mActionItems.removeAt(itemIndex);
        }
    };

    Q_INVOKABLE void updateActionItemConfigurations(int index, int itemIndex, QString mAction, QVariant mValue, QString mTime, int mRepeat, int mInterval) {
        if (itemIndex >= config.mActionGroupConfigurations[index].mActionItems.length()) {
            qWarning() << "Tried up update action list element that was beoynd end of list";
            return;
        }
        config.mActionGroupConfigurations[index].mActionItems[itemIndex].mAction = mAction;
        config.mActionGroupConfigurations[index].mActionItems[itemIndex].mValue = mValue;
        config.mActionGroupConfigurations[index].mActionItems[itemIndex].mTime = mTime;
        config.mActionGroupConfigurations[index].mActionItems[itemIndex].mRepeat = mRepeat;
        config.mActionGroupConfigurations[index].mActionItems[itemIndex].mInterval = mInterval;
    };

    Q_INVOKABLE void saveActionItemConfigurations() {
        ConfigurationWriter c;
        c.updateNodes("action_set", "actions.xml", getActionConfigurationAsMap());
    };

private:
    Config config;
    QDomDocument validateConfigFile(QString config);

};


#endif // CONFIGURATION_H
