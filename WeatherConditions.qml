import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml.Models 2.2
import QtCharts
import smah.weatherdata
import "weathercalcs.js" as WC



Item {
    id: weatherSunCalc
    width: 800
    height: 800
    Rectangle {
        id: current
        width: 600
        height: 300
        color: "#99000000"
        radius: 20
        SMAHLabel {
            id: templabel
            x:50
            y:100
            font.pixelSize: 48
            text: weatherdataitems[0].temp.toFixed(1) + "F\n" + weatherdataitems[0].rh + "%"
        }
        Column {
            id: spacer
            anchors.left: templabel.right
            width: 50
        }

        SMAHLabel {
            id: feelslikeLabel
            anchors.top: current.top
            anchors.left: spacer.right
            font.pixelSize: 20
            text: "Feels like"
        }
        SMAHLabel {
            id: feelslikeVal
            anchors.top: feelslikeLabel.top
            anchors.right: current.right
            font.pixelSize: 20
            text: "Feels like"
        }
        SMAHLabel {
            id: dewpointLabel
            anchors.top: feelslikeLabel.bottom
            anchors.left: feelslikeLabel.left
            font.pixelSize: 20
            text: "Dewpoint"
        }
        SMAHLabel {
            id: dewpointVal
            anchors.top: dewpointLabel.top
            anchors.right: current.right
            font.pixelSize: 20
            text: ""
        }
        SMAHLabel {
            id: windLabel
            anchors.top: dewpointLabel.bottom
            anchors.left: dewpointLabel.left
            font.pixelSize: 20
            text: "Wind"
        }
        SMAHLabel {
            id: windVal
            anchors.top: windLabel.top
            anchors.right: current.right
            font.pixelSize: 20
            text: ""
        }
        SMAHLabel {
            id: windGustLabel
            anchors.top: windLabel.bottom
            anchors.left: windLabel.left
            font.pixelSize: 20
            text: "Wind Gust"
        }
        SMAHLabel {
            id: windGustVal
            anchors.top: windGustLabel.top
            anchors.right: current.right
            font.pixelSize: 20
            text: ""
        }
        SMAHLabel {
            id: uvLabel
            anchors.top: windGustVal.bottom
            anchors.left: windLabel.left
            font.pixelSize: 20
            text: "UV Index"
        }
        SMAHLabel {
            id: uvVal
            anchors.top: uvLabel.top
            anchors.right: current.right
            font.pixelSize: 20
            text: ""
        }
    }
/*
    ChartView {
        id: chartView
        title: "Weather forecast"
        anchors.top: parent.top
        anchors.left: parent.left
        legend.alignment: Qt.AlignTop
        antialiasing: true
        height: 500
        width: 800
        visible: false
        //![2]
        BarCategoryAxis {
            id: barCategoriesAxis
            titleText: "Date"
        }

        ValueAxis{
            id: valueAxisY2
            min: 0
            max: 10
            titleText: "Rainfall [mm]"
        }

        ValueAxis {
            id: valueAxisX
            // Hide the value axis; it is only used to map the line series to bar categories axis
            visible: false
            min: 0
            max: 5
        }

        ValueAxis{
            id: valueAxisY
            min: 0
            max: 15
            titleText: "Temperature [&deg;C]"
        }

        LineSeries {
            id: maxTempSeries
            axisX: valueAxisX
            axisY: valueAxisY
            name: "Max. temperature"
        }

        LineSeries {
            id: minTempSeries
            axisX: valueAxisX
            axisY: valueAxisY
            name: "Min. temperature"
        }

        BarSeries {
            id: myBarSeries
            axisX: barCategoriesAxis
            axisYRight: valueAxisY2
            BarSet {
                id: rainfallSet
                label: "Rainfall"
            }
        }
    }
*/
    Row {
        id: weatherDayRow
        anchors.top: current.bottom
        anchors.topMargin: 200
        spacing: 40
        ListModel {
            id: weatherDayModel
        }

        Repeater {
            model: weatherDayModel
            delegate: SMAHLabel {
                width: 100
                text: weatherText
            }
        }
    }

    Row {
        id: weatherImageRow
        anchors.top: weatherDayRow.bottom
        height: 50
        spacing: 40
        ListModel {
            id: weatherImageModel
        }
        Repeater {
            id: repeater
            model: weatherImageModel
            delegate: Image {
                source: imageSource
                width: 100
                height: width
                fillMode: Image.PreserveAspectCrop
            }
        }
    }
    Row {
        id: weatherTextRow
        anchors.top: weatherImageRow.bottom
        anchors.topMargin: 50
        spacing: 40
        ListModel {
            id: weatherTextModel
        }
        Repeater {
            id: textrepeater
            model: weatherTextModel
            delegate: SMAHLabel {
                width: 100
                text: weatherText
                wrapMode: Text.WordWrap
            }
        }
    }

    Timer {
        interval: 1000; running: true; repeat: true;
        onTriggered: {
            var temp = weatherdataitems[0].temp.toFixed(1)
            var rh = weatherdataitems[0].rh
            var wind = weatherdataitems[0].windspeed
            var windgust = weatherdataitems[0].maxwindgust
            var uv = weatherdataitems[0].uv


            feelslikeVal.text = WC.heatIndexFahrenheit(temp, rh).toFixed(1)
            var dewpoint = WC.celsiusToFahrenheit(WC.dewPoint(WC.fahrenheitToCelsius(temp), rh)).toFixed(1)
            dewpointVal.text = WC.celsiusToFahrenheit(WC.dewPoint(WC.fahrenheitToCelsius(temp), rh)).toFixed(1)
            windVal.text = wind
            windGustVal.text = windgust
            uvVal.text = uv
            var dewpointColor = "#ffffff"
            if (dewpoint <= 51 )
                dewpointColor = "#0e5078"
            if (dewpoint >= 52 && dewpoint <= 55 )
                dewpointColor = "#70bb20"
            if (dewpoint >= 57 && dewpoint <= 70 )
                dewpointColor = "#4a6011"
            dewpointVal.color = dewpointColor
        }
    }
    Timer {
        interval: 60*60
        repeat: true
        triggeredOnStart: true
        running: true
        onTriggered: {
            var xhr = new XMLHttpRequest;
            xhr.open("GET",
                     "https://api.weather.gov/gridpoints/SEW/107,55/forecast");
            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.DONE) {
                    var a = JSON.parse(xhr.responseText);
                    parseWeatherData(a);

                }
            }
            xhr.send();
        }
    }
    function parseWeatherData(weatherData) {
        // Clear previous values
        //maxTempSeries.clear();
        //minTempSeries.clear();
        weatherImageModel.clear();
        weatherTextModel.clear();
        weatherDayModel.clear();
        //![4]
        // Loop through the parsed JSON
        for (var i in weatherData.properties.periods) {
            var weatherObj = weatherData.properties.periods[i];
            //![4]

            //![5]
            // Store temperature values, rainfall and weather icon.
            // The temperature values begin from 0.5 instead of 0.0 to make the start from the
            // middle of the rainfall bars. This makes the temperature lines visually better
            // synchronized with the rainfall bars.
            if (weatherObj.isDaytime === true) {
                //maxTempSeries.append(Number(i) + 0.5, weatherObj.temperature);
                weatherImageModel.append({"imageSource":weatherObj.icon});
                weatherTextModel.append({"weatherText":weatherObj.shortForecast})
                weatherDayModel.append({"weatherText":weatherObj.name})

            } else {
                //minTempSeries.append(Number(i) + 0.5, weatherObj.temperature);
                if ( i <= 5 )
                {
                    weatherImageModel.append({"imageSource":weatherObj.icon});
                    weatherTextModel.append({"weatherText":weatherObj.shortForecast})
                    weatherDayModel.append({"weatherText":weatherObj.name})

                }

            }
            //rainfallSet.append(weatherObj.precipMM);
            //![5]

            // Update scale of the chart
            //valueAxisY.max = Math.max(chartView.axisY().max, weatherObj.temperature);
            //valueAxisY2.max = Math.max(valueAxisY2.max, weatherObj.precipMM);
            //valueAxisX.min = 0;
            //valueAxisX.max = Number(i) + 1;

            // Set the x-axis labels to the dates of the forecast
            //var xLabels = barCategoriesAxis.categories;
            //xLabels[Number(i)] = weatherObj.startTime.substring(5, 10);
            //barCategoriesAxis.categories = xLabels;
            //barCategoriesAxis.visible = true;
            //barCategoriesAxis.min = 0;
            //barCategoriesAxis.max = xLabels.length - 1;
        }
    }
}
