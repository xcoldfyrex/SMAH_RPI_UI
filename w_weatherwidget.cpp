#include "w_weatherwidget.h"
#include "ui_weatherwidget.h"

#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QDebug>

WeatherWidget::WeatherWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WeatherWidget)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager();
    QObject::connect(manager, &QNetworkAccessManager::finished,
            this, [=](QNetworkReply *reply) {
                if (reply->error()) {
                    qDebug() << reply->errorString();
                    return;
                }

                QString answer = reply->readAll();
                jsonLoader(QJsonDocument::fromJson(answer.toUtf8()));

            }
        );
    request.setUrl(QUrl("https://api.darksky.net/forecast/00aac31807be8bd7e0c222204e181077/47.53,-122.64?exclude=minutely"));
    manager->get(request);
    //QString val;
    //QFile file;
    //file.setFileName("/home/lenny/fc.json");
    //file.open(QIODevice::ReadOnly | QIODevice::Text);
    //val = file.readAll();
    //file.close();
    //jsonLoader(QJsonDocument::fromJson(val.toUtf8()));
}

WeatherWidget::~WeatherWidget()
{
    delete ui;
}

void WeatherWidget::jsonLoader(QJsonDocument document){
    this->current = document.object()["currently"].toObject();
    this->hourly = document.object()["hourly"].toObject();
    this->daily = document.object()["daily"].toObject();
    updateWeatherDisplay();
}
QJsonObject WeatherWidget::getWeather()
{

}
void WeatherWidget::updateWeatherDisplay()
{
    QMap <int,QLabel*>daylabels;
    daylabels.insert(0, this->ui->lblDay0);
    daylabels.insert(1, this->ui->lblDay1);
    daylabels.insert(2, this->ui->lblDay2);
    daylabels.insert(3, this->ui->lblDay3);

    QMap <int,QLabel*>fclabels;
    fclabels.insert(0, this->ui->lblFCDay0);
    fclabels.insert(1, this->ui->lblFCDay1);
    fclabels.insert(2, this->ui->lblFCDay2);
    fclabels.insert(3, this->ui->lblFCDay3);

    for (int day = 0; day < 4; day++) {
        QJsonArray arr = daily["data"].toArray();
        QJsonObject dayo = arr[day].toObject();
        int ts = dayo.value("time").toInt();
        QDateTime dow = QDateTime::fromSecsSinceEpoch(ts);
        QString sr = QDateTime::fromSecsSinceEpoch(dayo.value("sunriseTime").toInt()).toString("HH:mm");
        QString ss = QDateTime::fromSecsSinceEpoch(dayo.value("sunsetTime").toInt()).toString("HH:mm");

        daylabels.value(day)->setText(dow.toString("ddd MM/dd"));
        fclabels.value(day)->setText(dayo.value("summary").toString() + "\n"
                                     + dayo.value("precipType").toString() + " " + QString::number(dayo.value("precipProbability").toDouble() * 100) + "%\n"
                                     + "HIGH: " + QString::number(static_cast<int>(dayo.value("temperatureMax").toDouble())) + ", "
                                     + "LOW: " + QString::number(static_cast<int>(dayo.value("temperatureMin").toDouble())) + "\n"
                                     + "SUNRISE: " + sr + ", "
                                     + "SUNSET: " + ss + "\n"

                    );
    }
}
