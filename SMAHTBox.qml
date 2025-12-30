import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects
import Qt5Compat.GraphicalEffects

Item {
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
}

/*
    background:
        GaussianBlur
    {
        id: theBlur;
        visible: true;
        anchors.fill: parent;
        source: tbox.parent;
        radius: 16
        samples: 72
    }
