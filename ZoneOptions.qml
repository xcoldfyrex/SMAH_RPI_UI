// menu with functions for each zone

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import smah.zone 1.0
import smah.light 1.0

import "zoneManagement.js" as ZoneCreation

Page {
    SMAHBackground {}
    z: -1000
    property string zoneName: "_DEF"
    property var deviceView: ""
    property var lights: ({})
    visible: true
    title: qsTr(zoneName)
    id: zoneOptions

    Rectangle {
        id: frame
        color: "#08111d"
        opacity: 0.9
        border.color: "#00000000"
        width: 300
        height:parent.height
        Column {
            parent: frame
            anchors.fill: parent
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Overview")
                    font.pixelSize: 32
                }
                width: parent.width
                onClicked: {
                    stackViewZoneOptions.clear()
                    stackViewZoneOptions.push(ZoneCreation.zoneOverviewMap[zoneName])
                }
            }
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Devices")
                    font.pixelSize: 32
                }
                width: parent.width
                onClicked: {
                    stackViewZoneOptions.clear()
                    stackViewZoneOptions.push(ZoneCreation.zoneDeviceMap[zoneName])
                    //ZoneCreation.zoneDeviceMap[zoneName]
                }
            }
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Climate Control")
                    font.pixelSize: 32
                }
                width: parent.width
                onClicked: {
                    //stackView.push("Page1Form.ui.qml")
                }
            }
        }
    }
    StackView
    {
        //parent: zoneOptions
        id: stackViewZoneOptions
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: frame.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        Component.onCompleted: {
            var component = Qt.createComponent("DeviceView.qml")
            var loadwin = component.createObject(stackViewZoneOptions, {zoneName: zoneName, lights: lights})
            ZoneCreation.zoneDeviceMap[zoneName] = loadwin
            var component_o = Qt.createComponent("ZoneOverview.qml")
            var loadwin_o = component_o.createObject(stackViewZoneOptions, {zoneName: zoneName, lights: lights})
            ZoneCreation.zoneOverviewMap[zoneName] = loadwin_o
            stackViewZoneOptions.clear()
        }
    }
}



/*


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:7;anchors_height:465;anchors_width:409;anchors_x:206;anchors_y:0}
}
##^##*/
