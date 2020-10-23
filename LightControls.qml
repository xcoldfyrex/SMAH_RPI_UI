import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import smah.light 1.0

Item {
    property int light_type: 0
    property int light_id: 0
    property var light_name: "_DEF"
   // width: parent.width
    //height: 50
    //color: "#040000"

    SMAHLabel {
        id: txtName
        text: qsTr(light_name)
        //anchors.left: parent.left
        //anchors.leftMargin: 15
        //anchors.top: parent.top
        //anchors.topMargin: 8
        font.pixelSize: 20
    }

    Slider {
        id: slider
        x: 179
        y: 10
        width: 302
        height: 22
        value: 0.5
    }

    SMAHLabel {
        id: txtValue
        x: 517
        width: 45
        height: 15
        text: qsTr("Text")
        //anchors.top: parent.top
        //anchors.topMargin: 8
        font.pixelSize: 20
    }

    Button {
        id: button
        x: 694
        y: 10
        text: qsTr("Button")
    }
}
/*##^##
Designer {
    D{i:1;anchors_x:15;anchors_y:8}D{i:3;anchors_y:17}
}
##^##*/
