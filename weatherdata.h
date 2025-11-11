#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>

class WeatherData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rh READ getHumidity NOTIFY updatedVal)
    Q_PROPERTY(float temp READ getTemperature NOTIFY updatedVal)
    Q_PROPERTY(float windspeed READ getWindSpeed NOTIFY updatedVal)
    Q_PROPERTY(float maxwindgust READ getWindSpeed NOTIFY updatedVal)
    Q_PROPERTY(float uv READ getUV NOTIFY updatedVal)



public:
    explicit WeatherData();
    float getTemperature() { return tempf; }
    int getHumidity() { return humidity; }
    int getUV() { return uv; }
    float getWindSpeed() { return windspeed; }
    float getMaxWindGust() { return maxwindgust; }


    void setHumidity(int val) {
        humidity = val;
        emit updatedVal();
    }
    void setTemperature(float val) {
        tempf = val;
        emit updatedVal();
    }
    void setWindSpeed(float val) {
        windspeed = val;
        emit updatedVal();
    }
    void setWindMaxGust(float val) {
        maxwindgust = val;
        emit updatedVal();
    }
    void setUV(float val) {
        uv = val;
        emit updatedVal();
    }
private:
    float tempf = 0;
    int humidity = 0;
    float solarrad = 0;
    float windspeed = 0;
    int uv = 0;
    float maxwindgust = 0;
    int winddir = 0;
    QList<float> rain;

signals:
    void updatedVal();
};

#endif // WEATHERDATA_H
