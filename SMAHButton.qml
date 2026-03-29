import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt5Compat.GraphicalEffects

Button {
    // Custom hover property since Button doesn't expose it by default
    //property bool hovered: false

    id: button
    flat: true
    height: 60
    implicitWidth: 180

    // Smooth color transitions
    palette.buttonText: button.down ? "#ffffff" : "#d4d4d4"

    contentItem: Text {
        text: button.text
        font: button.font
        opacity: button.enabled ? 1.0 : 0.4
        color: button.palette.buttonText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

        Behavior on color {
            ColorAnimation { duration: 150 }
        }
    }

    background: Rectangle {
        id: backgroundRect
        implicitHeight: 60
        implicitWidth: parent.implicitWidth
        radius: 8

        // Gradient background for depth
        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: button.down ? "#1a1d28" : (button.hovered ? "#1e2230" : "#16182080")
            }
            GradientStop {
                position: 1.0
                color: button.down ? "#0f1118" : (button.hovered ? "#16182a" : "#12141c80")
            }
        }

        // Subtle border with glow effect
        border.width: button.activeFocus ? 2 : 1
        border.color: button.activeFocus ? "#4a9eff" : (button.hovered ? "#555555" : "#333333")

        // Smooth transitions
        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }

        Behavior on border.width {
            NumberAnimation { duration: 150 }
        }

        // Outer glow effect when focused
        layer.enabled: button.activeFocus
        layer.effect: Glow {
            samples: 15
            color: "#4a9eff"
            spread: 0.3
            radius: 8
        }

        // Inner highlight for pressed state
        Rectangle {
            anchors.fill: parent
            anchors.margins: 1
            radius: parent.radius - 1
            color: "transparent"
            border.width: 1
            border.color: button.down ? "#ffffff15" : "#ffffff08"
            visible: !button.flat || button.down || button.hovered

            Behavior on border.color {
                ColorAnimation { duration: 150 }
            }
        }

        // Ripple effect container
        Item {
            id: rippleContainer
            anchors.fill: parent
            clip: true

            Rectangle {
                id: ripple
                width: 0
                height: 0
                radius: width / 2
                color: "#ffffff20"
                x: rippleContainer.width / 2
                y: rippleContainer.height / 2

                ParallelAnimation {
                    id: rippleAnimation
                    running: false

                    NumberAnimation {
                        target: ripple
                        property: "width"
                        from: 0
                        to: rippleContainer.width * 2
                        duration: 400
                        easing.type: Easing.OutCubic
                    }

                    NumberAnimation {
                        target: ripple
                        property: "height"
                        from: 0
                        to: rippleContainer.height * 2
                        duration: 400
                        easing.type: Easing.OutCubic
                    }

                    NumberAnimation {
                        target: ripple
                        property: "opacity"
                        from: 1.0
                        to: 0.0
                        duration: 400
                        easing.type: Easing.OutCubic
                    }
                }
            }
        }

        // Scale animation on press
        scale: button.down ? 0.96 : 1.0

        Behavior on scale {
            NumberAnimation {
                duration: 100
                easing.type: Easing.OutCubic
            }
        }
    }

    // Trigger ripple on click
    onPressed: {
        ripple.x = rippleContainer.width / 2
        ripple.y = rippleContainer.height / 2
        rippleAnimation.restart()
    }

    // Hover cursor
    MouseArea {
        id: hoverArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.NoButton  // Don't consume clicks

        //onEntered: button.hovered = true
        //onExited: button.hovered = false
    }


}