import QtQuick
import QtQuick.Controls 2.13
import QtQuick.Controls.Material
import ".."

CheckBox {
    id: control
    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "#ffffff"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
