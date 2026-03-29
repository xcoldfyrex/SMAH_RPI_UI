import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.shellyrgbw
import smah.objectfactory

import "."
import "qrc:/SMAHComponents"

Item {
    id: page
    visible: true
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]
    property var window

    SMAHTBox {
        id: mainContainer
        headerText: "Status"
        // System Info Grid
        GridLayout {
            id: grid
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 10
            columnSpacing: 20
            rowSpacing: 10
            columns: 2

            property var titles: [ "Build Number", "Build Date", "IP", "Z-Wave Socket" ]
            property var values: [ b_build, b_date, net_ip, "X" ]

            Repeater {
                model: grid.titles
                SMAHLabel {
                    Layout.row: index
                    Layout.column: 0
                    text: modelData
                    font.pixelSize: Style.fontCellSize
                    color: Style.fontHeaderColor
                    horizontalAlignment: Text.AlignRight
                }
            }

            Repeater {
                model: grid.values
                SMAHLabel {
                    Layout.row: index
                    Layout.column: 1
                    text: modelData
                    font.pixelSize: Style.fontCellSize
                    horizontalAlignment: Text.AlignLeft
                }
            }
        }

        // Section Label
        SMAHLabel {
            id: header2
            anchors.top: grid.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            text: "Shelly Devices"
            font.pixelSize: Style.fontHeaderSize
            color: "white"
        }

        // Column Headers
        Row {
            id: columnHeaders
            anchors.top: header2.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: 10
            anchors.leftMargin: 10
            spacing: 0

            property var headers: [ "Device ID", "Host", "Power", "Current", "Temp.", "Type", "FW", "Model", "Name" ]
            property var widths: [ 300, 350, 100, 100, 100, 200, 100, 200, 100 ]

            Repeater {
                model: columnHeaders.headers
                SMAHLabel {
                    text: modelData
                    width: columnHeaders.widths[index]
                    leftPadding: 5
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontColumnHeaderSize
                    font.bold: true
                    color: "#9c806e"
                }
            }
        }

        // Device List
        ListView {
            id: listView
            clip: true
            model: factory.getShellyObjects()
            anchors.top: columnHeaders.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: quit.top
            anchors.topMargin: 5
            anchors.leftMargin: 10
            anchors.bottomMargin: 10
            spacing: 2

            ScrollBar.vertical: ScrollBar {}

            delegate: Component {
                Item {
                    height: 35
                    width: listView.width

                    Row {
                        width: parent.width
                        spacing: 0

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].id
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 300
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].host
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 350
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000
                                  ? (factory.getShellyObjects()[index].app === "PlusWallDimmer"
                                     ? ""
                                     : factory.getShellyObjects()[index].message["apower"] + "W")
                                  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 100
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000
                                  ? (factory.getShellyObjects()[index].app === "PlusWallDimmer"
                                     ? ""
                                     : factory.getShellyObjects()[index].message["current"] + "A")
                                  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 100
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000
                                  ? (factory.getShellyObjects()[index].app === "PlusWallDimmer"
                                     ? ""
                                     : factory.getShellyObjects()[index].message["temperature"]["tF"] + "Â°F")
                                  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 100
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].app
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 200
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].ver
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 100
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].model
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 200
                        }

                        SMAHLabel {
                            text: factory.getShellyObjects()[index].name
                            leftPadding: 5
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontSmallSize
                            width: 100
                        }
                    }
                }
            }
        }

        SMAHButton {
            id: quit
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 10
            onClicked: Qt.quit()
            text: "Restart"
        }
    }
}