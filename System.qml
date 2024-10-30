import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor 1.0

//test
//import QtQuick.Controls.Styles 1.4

Page {
    id: page
    title: "System"
    visible: true
    SMAHBackground {}
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]

    GridLayout {
        id: grid
        columnSpacing: 0
        anchors.margins: 5
        x: mainMenu.width
        property var titles: [ "BUILD NUMBER", "BUILD DATE", "IP", "MAC", "Z-WAVE STATUS" ]
        property var values: [ b_build, b_date, net_ip, net_mac, z_driver ]
        anchors.leftMargin: 5
        anchors.top: header1.bottom
        anchors.topMargin: 16
        anchors.bottom: parent.top
        anchors.bottomMargin: -168
        rows: 10
        columns: 10
        anchors.rightMargin: -409

        Repeater {
            model: grid.titles
            SMAHLabel {
                Layout.row: index
                Layout.column: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
                font.pixelSize: 20
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
                font.pixelSize: 20
            }
        }
    }



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
