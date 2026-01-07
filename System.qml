import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.shellyrgbw
import smah.objectfactory

import "."
import "SMAHComponents/"

Page {
    id: page
    title: "System"
    visible: true
    SMAHBackground {}
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]
    property var window
    SMAHTBox {
        SMAHHeader {
            id: header1
            y: 0
            width: 600
            Text {
                id: element
                color: "#ffffff"
                text: qsTr("System Overview")
                anchors.fill: parent
                anchors.centerIn: parent
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: Style.fontHeaderSize
            }
        }
        GridLayout {
            id: grid
            columnSpacing: 10
            property var titles: [ "Build Number", "Build Date", "IP", "Z-Wave Socket",  ]
            property var values: [ b_build, b_date, net_ip, "X" ]
            anchors.leftMargin: 5
            anchors.top: header1.bottom
            anchors.topMargin: 16
            //anchors.bottom: parent.top
            anchors.bottomMargin: -200
            rows: 5
            columns: 3

            Repeater {
                model: grid.titles
                SMAHLabel {
                    Layout.row: index
                    Layout.column: 0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: modelData
                    font.pixelSize: Style.fontCellSize
                    color: Style.fontHeaderColor
                }
            }

            Repeater {
                model: grid.values
                SMAHLabel {
                    Layout.row: index
                    Layout.column: 1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: modelData
                    font.pixelSize: Style.fontCellSize
                    Layout.alignment: Qt.AlignVCenter
                }
            }
        }


        SMAHHeader {
            id: header2
            anchors.top: grid.bottom
            anchors.topMargin: 60
            width: 600
            Text {
                color: "#ffffff"
                text: qsTr("Shelly Devices")
                anchors.fill: parent
                anchors.centerIn: parent
                verticalAlignment: Qt.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: Style.fontHeaderSize
            }
        }
        ListView {
            id: listView
            clip: true
            model: factory.getShellyObjects()
            anchors.top: header2.bottom
            width: parent.width
            anchors.bottom: quit.top
            ScrollBar.vertical: ScrollBar {}
            Repeater {
                model: [ "Device ID", "Host", "Power", "Current", "Temp.", "Type", "FW", "Model", "Name" ]
                SMAHLabel {
                    text: modelData
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontColumnHeaderSize
                    color: "#9c806e"
                }
            }
            delegate: Component {
                Item {
                    height: 35
                    width: 300
                    Row {
                        width: parent.width
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].id
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 300
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].host
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 350
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000 ? (factory.getShellyObjects()[index].app === "PlusWallDimmer" ? "" : factory.getShellyObjects()[index].message["apower"] + "W")  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 100
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000 ? (factory.getShellyObjects()[index].app === "PlusWallDimmer" ? "" : factory.getShellyObjects()[index].message["current"] + "A" )  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 100
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].updated >= 5000 ? (factory.getShellyObjects()[index].app === "PlusWallDimmer" ? "" : factory.getShellyObjects()[index].message["temperature"]["tF"]+ "F")  : "Waiting.."
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 100
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].app
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 200
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].ver
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 100
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].model
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 200
                        }
                        SMAHLabel {
                            text: factory.getShellyObjects()[index].name
                            leftPadding: 5
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            font.pixelSize: Style.fontCellSize
                            width: 100
                        }
                    }
                }
                //anchors.fill: parent
                //contentHeight: shellyGridLayout.height
                //contentWidth: shellyGridLayout.width
                /*Row {
                id: shellyGridLayout

                Layout.fillWidth: true
                Layout.fillHeight: true

                property var shellytitles: [ "Device ID", "Host", "Power", "Current", "Temp.", "Type", "FW", "Model", "Name" ]
                /*
                Repeater {
                    model: shellyGridLayout.shellytitles
                    SMAHLabel {
                        Layout.row: 1
                        Layout.column: index
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: modelData
                        leftPadding: 5
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: Style.fontColumnHeaderSize
                        color: "#9c806e"
                    }
                }



                }*/

            }
        }

        SMAHButton {
            id: quit
            anchors.bottom: parent.bottom
            onClicked: Qt.quit()
            text: "Restart"
            x: mainMenu.width
        }
    }
}
