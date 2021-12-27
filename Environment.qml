import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor 1.0

Page {
    property var z_sensortitles: [ "Location", "F", "RH%", "Lux", "UV" ]

    SMAHBackground {}
    GridLayout {
        id: gridLayout
        height: 100
        columns: 10
        rows: 15
        //anchors.top: rectangle1.bottom
        ///anchors.topMargin: 16

        Repeater {
            model: z_sensortitles
            SMAHLabel {
                Layout.row: 1
                Layout.column: index
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 20
            }
        }

        Repeater {
            model: sensorList
            SMAHLabel {
                Layout.column: 0
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sensorList[index].name
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 16
            }
        }

        Repeater {
            model: sensorList
            SMAHLabel {
                Layout.column: 1
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sensorList[index].temperature.toFixed(1)
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 16
            }
        }

        Repeater {
            model: sensorList
            SMAHLabel {
                Layout.column: 2
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sensorList[index].rh
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 16
            }
        }

        Repeater {
            model: sensorList
            SMAHLabel {
                Layout.column: 3
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sensorList[index].lux
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 16
            }
        }

        Repeater {
            model: sensorList
            SMAHLabel {
                Layout.column: 4
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sensorList[index].uv
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 16
            }
        }
    }
}
