// menu with functions for each zone

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    property var sunloadwin
    property var weatherloadwin
    SMAHBackground {}
    title: qsTr("Weather")
    id: weatherHome
    SMAHTBox {
        ColumnLayout {
            anchors.fill: parent
            spacing: 0
            id: frame
            SMAHHeader {
                id: header1
                y: 0
                width: 600
                Text {
                    id: element
                    color: "#ffffff"
                    text: qsTr("Weather")
                    font.pixelSize: Style.fontHeaderSize
                }
            }
            TabBar {
                Layout.fillWidth: true
                id: bar
                background: Rectangle{
                    color: "#99000000"
                }
                TabButton {
                    background: Rectangle{
                        color: bar.currentIndex === 0 ? "grey" : "transparent"
                    }
                    text: qsTr("Current Conditions")
                    font.pixelSize: 32
                    onClicked: {
                        weatherView.clear()
                        weatherView.push(weatherloadwin)
                    }
                }
                TabButton {
                    background: Rectangle{
                        color: bar.currentIndex === 1 ? "grey" : "transparent"
                    }
                    text: qsTr("Sunrise/set")
                    font.pixelSize: 32
                    onClicked: {
                        weatherView.clear()
                        weatherView.push(sunloadwin)
                    }
                }
            }
            StackView
            {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                id: weatherView
                Layout.topMargin: 25
            }

            Component.onCompleted: {
                var weathercomponent = Qt.createComponent("WeatherConditions.qml")
                weatherloadwin = weathercomponent.createObject(weatherView)
                weatherloadwin.visible = false
                var suncomponent = Qt.createComponent("WeatherSunCalc.qml")
                sunloadwin = suncomponent.createObject(weatherView)
                sunloadwin.visible = false
                weatherloadwin.visible = true
                weatherView.push(weatherloadwin)
            }
        }
    }
}
