import QtQuick
import QtQuick.Controls 2.13
import QtQuick.Controls.Material
import ".."

RadioButton {
    id: control
    indicator: Rectangle {
        implicitWidth: 26
        implicitHeight: 26
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 0
        border.color: "#111111"

        Rectangle {
            width: 14
            height: 14
            x: 6
            y: 6
            radius: 0
            color: "#111111"
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "white"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
