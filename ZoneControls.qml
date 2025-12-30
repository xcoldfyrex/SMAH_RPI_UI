import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import smah.light
import smah.zone

import "qrc:/SMAHComponents/"

Item {
    property var lights
    property Zone zone
    property var parentObject
    id: controlView
    implicitWidth: parent.width
    implicitHeight: parent.height
    TabBar {
        id: bar
        background: Rectangle{
            color: "#99000000"
        }
        width: 900
        TabButton {
            background: Rectangle{
                color: bar.currentIndex === 0 ? "grey" : "transparent"
            }
            text: qsTr("Controls")
            font.pixelSize: 32
            onClicked: {
                elementView.currentIndex = 0
            }
        }
        TabButton {
            background: Rectangle{
                color: bar.currentIndex === 1 ? "grey" : "transparent"
            }
            text: qsTr("Scenes")
            font.pixelSize: 32
            onClicked: {
                elementView.currentIndex = 1
            }
        }
    }
    StackLayout
    {
        anchors.top: bar.bottom
        anchors.topMargin: 25
        implicitWidth: parent.width
        anchors.bottom: parent.bottom
        id: elementView
        ZoneElements {
            lights_: lights
            zone_: zone
            visible: true
            parentObject: elementView
        }
        ZoneScenes {
            lights_: lights
            zone_: zone
            visible: true
            parentObject: elementView
        }
    }
}
