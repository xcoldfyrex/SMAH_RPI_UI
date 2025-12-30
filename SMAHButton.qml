import QtQuick 2.0
import QtQuick.Controls 2.12


Button {
    id: button
    flat: true
    palette.buttonText: "#d4d4d4"

    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 50
        border.width: button.activeFocus ? 2 : 2
        border.color: "#ccc"
        radius: 3
        color:  {
            button.down ? "#12141C" : "#12141C"
            button.up ? "#12141C" : "#12141C"
        }
    }
}
