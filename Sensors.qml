import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor
import "."

Page {
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]
    id: page
    visible: true
    //height: 600

    SMAHBackground {}
    SMAHTBox {
        //width: gridLayout.width + 30
        //height: gridLayout.height + 30
        GridLayout {
            id: gridLayout
            x: parent.left + 60
            y: parent.top + 60
            height: 300
            columns: 10
            rows: 15
            Layout.fillWidth: true
            Layout.fillHeight: true

            //anchors{
            //    left: parent.left
            //   bottom: parent.bottom
            //   right: parent.right
            //   top: parent.top
            //}
            //required property int index

            Repeater {
                model: page.z_sensortitles
                SMAHLabel {
                    Layout.row: 1
                    Layout.column: index
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: modelData
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontHeaderSize
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
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: sensorList
                SMAHLabel {
                    Layout.column: 1
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: sensorList[index].updated >= 1000 ? sensorList[index].temperature.toFixed(1) : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: sensorList
                SMAHLabel {
                    Layout.column: 2
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: sensorList[index].updated >= 1000 ? sensorList[index].rh + "%" : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: sensorList
                SMAHLabel {
                    Layout.column: 3
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: sensorList[index].updated >= 1000 ? sensorList[index].lux : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: sensorList
                SMAHLabel {
                    Layout.column: 4
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: sensorList[index].updated >= 1000 ? sensorList[index].uv : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }
            Repeater {
                model: sensorList
                SMAHLabel {
                    Layout.column: 5
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: sensorList[index].updated >= 1000 ? Qt.formatDateTime(new Date(sensorList[index].updated * 1000), "MM/dd/yyyy hh:mm:ss") : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }
        }
    }
}

