import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor 1.0
import smah.shellyrgbw

import "."

//test
//import QtQuick.Controls.Styles 1.4

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
            property var titles: [ "Build Number", "Build Date", "IP", "MAC", "Z-Wave Socket",  ]
            property var values: [ b_build, b_date, net_ip, net_mac, "X" ]
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
        GridLayout {
            id: shellyGridLayout
            anchors.top: header2.bottom
            columns: 6
            rows: 10
            Layout.fillWidth: true
            Layout.fillHeight: true

            property var shellytitles: [ "Device ID", "HOST", "IP", "Power", "Current", "Temperature" ]

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

            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 0
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].id
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }

            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 1
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].ip
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }

            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 2
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].host
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }

            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 3
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["apower"] + "W" : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }

            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 4
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["current"] + "A" : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }
            Repeater {
                model: shellyRGBWList
                SMAHLabel {
                    Layout.column: 5
                    Layout.row: index + 2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["temperature"]["tF"] + "F" : "-"
                    leftPadding: 5
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: Style.fontCellSize
                }
            }
            Timer {
                interval: 100; running: true; repeat: true;
                onTriggered: {
                    //console.log(shellyRGBWList[0].message["temperature"]["tF"])
                }
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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:7;anchors_y:221}D{i:11;anchors_x:8;anchors_y:14}
D{i:10;anchors_x:5}D{i:13;anchors_x:8;anchors_y:14}D{i:12;anchors_x:5}
}
##^##*/
