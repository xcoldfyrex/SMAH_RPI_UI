import QtQuick 2.0
import QtQuick.Controls 2.12

Button {
    id: button
    flat: true
    palette.buttonText: "#d4d4d4"
    height: 50
    implicitWidth: 150
    background: Rectangle {
        implicitHeight: 50
        implicitWidth: parent.implicitWidth
        border.width: button.activeFocus ? 2 : 2
        border.color: "#ccc"
        radius: 3
        color:  {
            button.down ? "#12141C" : "#12141C"
            button.up ? "#12141C" : "#12141C"
        }
    }
}
