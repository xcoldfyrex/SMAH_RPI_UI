import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor
import smah.objectfactory

import "."
import "qrc:/SMAHComponents"

Item {
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]
    id: page
    visible: true
    SMAHTBox {
        headerText: "Environmental"
        GridLayout {
            id: gridLayout
            //anchors.top: header1.bottom
            height: 300
            columns: 10
            rows: 15
            Layout.fillWidth: true
            Layout.fillHeight: true

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
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 0
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].name
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 1
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].updated >= 1000 ? factory.getSensorObjects()[index].temperature.toFixed(1) : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 2
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].updated >= 1000 ? factory.getSensorObjects()[index].rh + "%" : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 3
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].updated >= 1000 ? factory.getSensorObjects()[index].lux : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }

            Repeater {
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 4
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].updated >= 1000 ? factory.getSensorObjects()[index].uv : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }
            Repeater {
                model: factory.getSensorObjects()
                SMAHLabel {
                    Layout.column: 5
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: factory.getSensorObjects()[index].updated >= 1000 ? Qt.formatDateTime(new Date(factory.getSensorObjects()[index].updated * 1000), "MM/dd/yyyy hh:mm:ss") : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 22
                }
            }
        }
    }
}

