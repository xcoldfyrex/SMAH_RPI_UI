// menu with functions for each zone

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    property var sunloadwin
    property var weatherloadwin
    SMAHBackground {}
    z: -1000
    title: qsTr("Weather")
    id: weatherHome
    SMAHMenu {
        id: frame
        Column {
            parent: frame
            anchors.fill: parent
            SMAHButton {
                SMAHLabel {
                    text: qsTr("Current Conditions")
                    font.pixelSize: 32
                }
                width: parent.width
                height: 40
                onClicked: {
                    weatherView.clear()
                    weatherView.push(weatherloadwin)
                }
            }
            SMAHButton {
                SMAHLabel {
                    text: qsTr("Sunrise/set")
                    font.pixelSize: 32
                }
                width: parent.width
                height: 40

                onClicked: {
                    weatherView.clear()
                    weatherView.push(sunloadwin)
                }
            }
        }
    }
    StackView
    {
        //parent: zoneOptions
        id: weatherView
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: frame.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        Component.onCompleted: {
            weatherView.clear()
            weatherView.push(sunloadwin)
        }
    }
    Component.onCompleted: {
        var weathercomponent = Qt.createComponent("WeatherConditions.qml")
        weatherloadwin = weathercomponent.createObject(weatherView)
        var suncomponent = Qt.createComponent("WeatherSunCalc.qml")
        sunloadwin = suncomponent.createObject(weatherView)
    }
}
