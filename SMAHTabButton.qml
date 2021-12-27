import QtQuick 2.0
import QtQuick.Controls 2.13


TabButton {
    id: tb
    background: Rectangle {
        border.width: parent.activeFocus ? 2 : 1
        color: "#111111"
        height: tb.height
        border.color: "#888"
        radius: 4
        gradient: Gradient {
            GradientStop { position: 0 ; color: tb.pressed ? "#ccc" : "#eee" }
            GradientStop { position: 1 ; color: tb.pressed ? "#aaa" : "#ccc" }
        }
    }
}
