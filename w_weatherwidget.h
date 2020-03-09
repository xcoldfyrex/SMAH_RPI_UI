#ifndef W_WEATHERWIDGET_H
#define W_WEATHERWIDGET_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class WeatherWidget;
}

class WeatherWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WeatherWidget(QWidget *parent = nullptr);
    ~WeatherWidget();

private:
    Ui::WeatherWidget *ui;
    QJsonObject current;
    QJsonObject hourly;
    QJsonObject daily;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    void jsonLoader(QJsonDocument document);
    void updateWeatherDisplay();
    QJsonObject getWeather();
};

#endif // W_WEATHERWIDGET_H
