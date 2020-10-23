import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.sensor 1.0

Page {
    id: page
    title: "System"
    SMAHBackground {}
    property var z_sensornames: []
    property var z_sensortitles: [ "Device Name", "Temperature", "RH", "Lux", "UV", "Updated" ]

    GridLayout {
        id: grid
        columnSpacing: 0
        anchors.margins: 5

        property var titles: [ "BUILD NUMBER", "BUILD DATE", "IP", "MAC", "Z-WAVE DRIVER", "Z-WAVE ID" ]
        property var values: [ b_build, b_date, net_ip, net_mac, z_driver, z_homeid ]
        anchors.leftMargin: 5
        anchors.top: rectangle.bottom
        anchors.topMargin: 16
        anchors.bottom: parent.top
        anchors.bottomMargin: -168
        anchors.right: parent.left
        anchors.left: parent.left
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

    GridLayout {
        id: gridLayout
        x: 5
        //width: 404
        height: 100
        columns: 10
        rows: 15
        anchors.top: rectangle1.bottom
        anchors.topMargin: 16

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
                color: "#fdfdfd"
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
                color: "#fdfdfd"
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

    Rectangle {
        id: rectangle
        y: 0
        width: 404
        height: 37
        color: "#08111d"
        anchors.left: parent.left
        anchors.leftMargin: 0

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

    Rectangle {
        id: rectangle1
        y: 188
        width: 404
        height: 37
        color: "#08111d"
        anchors.left: parent.left
        anchors.leftMargin: 0
        Text {
            id: element1
            color: "#ffffff"
            text: qsTr("Sensors")
            anchors.fill: parent
            font.pixelSize: 20
        }
    }

        Button {
            anchors.bottom: parent.bottom
            onClicked: Qt.quit()
            text: "Restart"
        }


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:7;anchors_y:221}D{i:11;anchors_x:8;anchors_y:14}
D{i:10;anchors_x:5}D{i:13;anchors_x:8;anchors_y:14}D{i:12;anchors_x:5}
}
##^##*/
