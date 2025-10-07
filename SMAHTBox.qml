import QtQuick 2.0
import QtQuick.Effects
Item {
    //anchors.horizontalCenter: parent.horizontalCenter
    //anchors.verticalCenter: parent.verticalCenter
    implicitWidth: window.width / 1.1
    implicitHeight: window.height / 1.1
    x: window.width / 2 - width / 2
    y: window.height / 2 - height / 2


    Rectangle {
        id: container
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: "#aa000000"
        width: parent.width
        implicitHeight: parent.height
        radius: 50
        anchors.margins: 100
    }
    MultiEffect {
        source: container
        anchors.fill: parent
        blurEnabled: true
        blurMax: 96
        blur: 1.0
    }
}
