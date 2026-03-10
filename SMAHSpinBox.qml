import QtQuick
import QtQuick.Controls 2.13
import QtQuick.Controls.Material
import ".."

SpinBox {
    width: 100
    height: 50
    editable: true
    id: control
    contentItem: TextInput {
        z: 2
        text: control.textFromValue(control.value, control.locale)
        font: control.font
        color: "white"
        selectionColor: "white"
        selectedTextColor: "#111111"
        horizontalAlignment: Qt.AlignHCenter
        verticalAlignment: Qt.AlignVCenter

        readOnly: !control.editable
        validator: control.validator
        inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    up.indicator: Rectangle {
        x: control.mirrored ? 0 : parent.width - width
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: control.up.pressed ? "#111111" : "#111111"
        border.color: enabled ? "#111111" : "#111111"

        Text {
            text: "+"
            font.pixelSize: control.font.pixelSize * 2
            color: "white"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    down.indicator: Rectangle {
        x: control.mirrored ? parent.width - width : 0
        height: parent.height
        implicitWidth: 40
        implicitHeight: 40
        color: control.down.pressed ? "#111111" : "#111111"
        border.color: enabled ? "#111111" : "#111111"

        Text {
            text: "-"
            font.pixelSize: control.font.pixelSize * 2
            color: "white"
            anchors.fill: parent
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: Rectangle {
        implicitWidth: 140
        color: "#111111"
    }
}
