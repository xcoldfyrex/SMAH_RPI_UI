import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor 1.0
import smah.shellyrgbw

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

    SMAHHeader {
        id: header1
        x: mainMenu.width
        y: 0
        width: 404
        height: 37
        Text {
            id: element
            color: "#ffffff"
            text: qsTr("System")
            anchors.fill: parent
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 20
        }
    }
    GridLayout {
        id: grid
        columnSpacing: 0
        anchors.margins: 5
        //x: mainMenu.width
        property var titles: [ "Build Number", "Build Date", "IP", "MAC", "Z-Wave Socket",  ]
        property var values: [ b_build, b_date, net_ip, net_mac, z_driver ]
        anchors.leftMargin: 5
        anchors.top: header1.bottom
        anchors.topMargin: 16
        anchors.bottom: parent.top
        anchors.bottomMargin: -168
        rows: 10
        columns: 10
        //anchors.rightMargin: -409

        Repeater {
            model: grid.titles
            SMAHLabel {
                Layout.row: index
                Layout.column: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
                font.pixelSize: 20
                color: "#9c806e"
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
                font.pixelSize: 14
            }
        }
    }


    SMAHHeader {
        id: header2
        x: mainMenu.width
        anchors.top: grid.bottom
        width: 404
        height: 37
        Text {
            color: "#ffffff"
            text: qsTr("Shelly Devices")
            anchors.fill: parent
            verticalAlignment: Text.AlignTop
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 20
        }
    }
    GridLayout {
        id: shellyGridLayout
        anchors.top: header2.bottom
        columns: 5
        rows: 10
        Layout.fillWidth: true
        Layout.fillHeight: true

        //anchors{
        property var shellytitles: [ "Device ID", "IP", "Power", "Current", "Temperature" ]
        //    left: parent.left
         //   bottom: parent.bottom
         //   right: parent.right
         //   top: parent.top
        //}
        //required property int index

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
                font.pixelSize: 20
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
                font.pixelSize: 14
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
                font.pixelSize: 14
            }
        }

        Repeater {
            model: shellyRGBWList
            SMAHLabel {
                Layout.column: 2
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["apower"] + "W" : "-"
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }

        Repeater {
            model: shellyRGBWList
            SMAHLabel {
                Layout.column: 3
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["current"] + "A" : "-"
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }
        Repeater {
            model: shellyRGBWList
            SMAHLabel {
                Layout.column: 4
                Layout.row: index + 2
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: shellyRGBWList[index].updated >= 1000 ? shellyRGBWList[index].message["temperature"]["tF"] + "F" : "-"
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }
        Timer {
            interval: 100; running: true; repeat: true;
            onTriggered: {
                //console.log(shellyRGBWList[0].message["temperature"]["tF"])
            }
        }
    }

    Button {
        id: quit
        anchors.bottom: parent.bottom
        onClicked: Qt.quit()
        text: "Restart"
        x: mainMenu.width

        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            border.width: activeFocus ? 2 : 1
            border.color: "#888"
            radius: 4
            gradient: Gradient {
                GradientStop { position: 0 ; color: "#ccc" }
                GradientStop { position: 1 ; color: "#aaa" }
            }

        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:7;anchors_y:221}D{i:11;anchors_x:8;anchors_y:14}
D{i:10;anchors_x:5}D{i:13;anchors_x:8;anchors_y:14}D{i:12;anchors_x:5}
}
##^##*/
