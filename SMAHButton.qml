import QtQuick 2.0
import QtQuick.Controls 2.12


Button {
    id: button
    flat: true
    palette.buttonText: "#d4d4d4"

    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 50
        border.width: button.activeFocus ? 0 : 0
        border.color: "#000"
        radius: 0
        color:  {
            button.down ? "#12141C" : "transparent"
            //button.up ? "#12141C" : "transparent"
        }

        //flat: true
        //border.width: 0
        //border.height: 0

        /*
        gradient: Gradient {
            GradientStop { position: 0 ; color: button.pressed ? "#000" : "#2a2f3b" }
            GradientStop { position: 1 ; color: button.pressed ? "#000" : "#2a2f3b" }
        }
        */
    }
}
