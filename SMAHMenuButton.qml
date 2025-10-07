import QtQuick 2.0

import QtQuick.Controls 2.12


Button {
    id: button
    flat: true
    palette.buttonText: "#d4d4d4"

    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 50
        border.width: 0
        border.color: "#000"
        radius: 3
        color:  {
            button.down ? "#12141C" : "transparent"
            //button.up ? "#12141C" : "transparent"
        }
    }
}
