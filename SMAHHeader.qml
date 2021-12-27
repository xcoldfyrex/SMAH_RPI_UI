import QtQuick 2.0
import QtQuick.Controls 2.13

Rectangle {
    id: inner
    anchors.left: parent.left
    anchors.leftMargin: 0
    border.width: 1
    color: "#00000000"
    Rectangle {
        rotation: 90
        x: ((parent.height / 2) * -1)  + (parent.width / 2)
        y: ((parent.width / 2) * -1)  + (parent.height / 2)
        height: parent.width
        width: parent.height
        //transformOrigin: parent.TopLeft
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#00000000"
            }
            GradientStop {
                position: 1
                color: "#ff08111d"
            }
        }
    }
}
