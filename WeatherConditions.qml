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
        id: tempCircle
        width: 300
        height: 300
        color: "transparent"
        border.width: 20
        radius: width*0.5
        SMAHLabel {
            id: templabel
            anchors.centerIn : parent
            font.pixelSize: 48
            text: weatherdataitems[0].temp.toFixed(1) + "F\n" + weatherdataitems[0].rh + "%"
        }
        SMAHLabel {
            id: feelslike
            anchors.top: tempCircle.bottom
            anchors.left: tempCircle.Center
            font.pixelSize: 32
            text: "F"
        }
        SMAHLabel {
            id: dewpointLabel
            anchors.top: feelslike.bottom
            anchors.left: feelslike.left
            font.pixelSize: 32
            text: "Dewpoint: "
        }
        SMAHLabel {
            id: dewpointVal
            anchors.top: dewpointLabel.top
            anchors.left: dewpointLabel.right
            font.pixelSize: 32
            text: ""
        }
    }

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

    Row {
           id: weatherImageRow
           anchors.top: chartView.bottom
           anchors.topMargin: 5
           anchors.bottom: poweredByText.top
           anchors.bottomMargin: 5
           anchors.horizontalCenter: parent.horizontalCenter
           height: 50//parent.height - chartView.height - anchors.topMargin

           ListModel {
               id: weatherImageModel
           }

           Repeater {
               id: repeater
               model: weatherImageModel
               delegate: Image {
                   source: imageSource
                   width: 100//weatherImageRow.height
                   height: width
                   fillMode: Image.PreserveAspectCrop
               }
           }
       }

       Text {
           id: poweredByText
           anchors.bottom: parent.bottom
           anchors.bottomMargin: 5
           anchors.left: parent.left
           anchors.leftMargin: 25
           height: parent.height / 25
           text: "Powered by World Weather Online"
       }
    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: {
            var color = "#ffffff"
            var temp = weatherdataitems[0].temp.toFixed(1)
            var rh = weatherdataitems[0].rh
            if(temp <= 20)
                color = "#bd00f7"
            if(temp >= 20.1 && temp <= 30)
                color = "#0035f7"
            if(temp >= 30.1 && temp <= 40)
                color = "#00a0f7"
            if(temp >= 40.1 && temp <= 50)
                color = "#00f78c"
            if(temp >= 50.1 && temp <= 60)
                color = "#adf700"
            if(temp >= 60.1 && temp <= 70)
                color = "#adf700"
            if(temp >= 70.1 && temp <= 80)
                color = "#f7ef00"
            if(temp >= 80.1 && temp <= 90)
                color = "#FFA500"
            if(temp >= 90.1)
                color = "#ff2600"
            tempCircle.border.color = color

            feelslike.text = "Feels like: " + WC.heatIndexFahrenheit(temp, rh).toFixed(1)
            var dewpoint = WC.celsiusToFahrenheit(WC.dewPoint(WC.fahrenheitToCelsius(temp), rh)).toFixed(1)
            dewpointVal.text = WC.celsiusToFahrenheit(WC.dewPoint(WC.fahrenheitToCelsius(temp), rh)).toFixed(1)
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
        maxTempSeries.clear();
        minTempSeries.clear();
        weatherImageModel.clear();

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
            maxTempSeries.append(Number(i) + 0.5, weatherObj.temperature);
                weatherImageModel.append({"imageSource":weatherObj.icon});
            } else {
                minTempSeries.append(Number(i) + 0.5, weatherObj.temperature);
                if ( i <= 5 ) weatherImageModel.append({"imageSource":weatherObj.icon});

            }
            //rainfallSet.append(weatherObj.precipMM);
            //![5]

            // Update scale of the chart
            valueAxisY.max = Math.max(chartView.axisY().max, weatherObj.temperature);
            //valueAxisY2.max = Math.max(valueAxisY2.max, weatherObj.precipMM);
            valueAxisX.min = 0;
            valueAxisX.max = Number(i) + 1;

            // Set the x-axis labels to the dates of the forecast
            var xLabels = barCategoriesAxis.categories;
            xLabels[Number(i)] = weatherObj.startTime.substring(5, 10);
            barCategoriesAxis.categories = xLabels;
            barCategoriesAxis.visible = true;
            barCategoriesAxis.min = 0;
            barCategoriesAxis.max = xLabels.length - 1;
        }
    }
}
