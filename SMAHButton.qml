import QtQuick 2.0
import QtQuick.Controls 2.12


Button {
    id: button
    background: Rectangle {
        implicitWidth: 150
        implicitHeight: 50
        border.width: button.activeFocus ? 2 : 1
        border.color: "#222630"
        radius: 4
        gradient: Gradient {
            GradientStop { position: 0 ; color: button.pressed ? "#000" : "#2a2f3b" }
            GradientStop { position: 1 ; color: button.pressed ? "#000" : "#2a2f3b" }
        }
    }      
}
