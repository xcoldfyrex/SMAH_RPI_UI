import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light
import smah.zone
import Qt5Compat.GraphicalEffects

import ".."
import "qrc:/SMAHComponents/"

Popup {
    property var lightPages: ({})
    property Zone zone
    property QtObject anchorParent

    id: popup
    background: Item {
        ShaderEffectSource {
            id: effectSource
            sourceItem: popup.parent
            anchors.fill: parent
            sourceRect: Qt.rect(popup.x,popup.y,popup.width,popup.height)
        }
        FastBlur{
            id: blur
            anchors.fill: effectSource
            source: effectSource
            radius: 32
        }
    }

    focus: true
    dim: false
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnReleaseOutside
    implicitWidth: parent.width / 1.4
    implicitHeight: parent.height / 1.1
    x: parent.width / 2 - width / 2
    y: 50
    Component.onCompleted:
    {
        if (zone.getLightList.length !== 0) {
            var zonecomponent = Qt.createComponent("ZoneElements.qml")
            var zoneloadwin = zonecomponent.createObject(zoneContent, {lights: zone.getLightList, zone: zone, parentObject: zoneContent})
        }
    }
    SMAHTBox {
        implicitWidth: parent.width
        implicitHeight: parent.height
        x: parent.x
        y: parent.y
        id: box
        SMAHHeader {
            id: header
            y: 0
            width: 600
            Layout.alignment: Qt.AlignCenter
            Text {
                id: element
                color: "#ffffff"
                text: zone.getName
                font.pixelSize: Style.fontHeaderSize
            }
        }
    }
    StackView {
        id: zoneContent
        anchors.fill: parent
        anchors.topMargin: 100
        anchors.leftMargin: 100

    }
}
