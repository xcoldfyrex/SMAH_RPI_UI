import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects

import ".."

ComboBox {
    property int popupHeight: 300
    property int popupWidth: 300

    id: control
    font.pointSize: Style.fontCellSize

    // Touch-friendly height matching SMAHButton
    implicitHeight: 60
    leftPadding: 15
    rightPadding: 45 // Space for chevron
    // Custom indicator (chevron)
    indicator: Item {
        x: control.width - width - 15
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 24
        height: 24

        Canvas {
            id: chevron
            anchors.fill: parent
            rotation: control.popup.visible ? 180 : 0

            Behavior on rotation {
                NumberAnimation {
                    duration: 200
                    easing.type: Easing.OutCubic
                }
            }

            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.strokeStyle = "#4a9eff"
                ctx.lineWidth = 2
                ctx.lineCap = "round"
                ctx.lineJoin = "round"

                // Draw chevron down
                ctx.beginPath()
                ctx.moveTo(6, 9)
                ctx.lineTo(12, 15)
                ctx.lineTo(18, 9)
                ctx.stroke()
            }
        }
    }

    delegate: ItemDelegate {
        width: control.width
        height: 50 // Touch-friendly delegate height
        leftPadding: 15

        contentItem: Text {
            text: modelData
            color: "white"
            font.pointSize: Style.fontHeaderSize
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        highlighted: control.highlightedIndex === index

        background: Rectangle {
            color: parent.highlighted ? "#4a9eff" : (parent.hovered ? "#ffffff15" : "transparent")
            radius: 5

            Behavior on color {
                ColorAnimation { duration: 150 }
            }
        }
    }

    contentItem: Text {
        text: control.displayText
        font: control.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight

    }

    background: Rectangle {
        id: bgRect
        implicitWidth: popupWidth
        implicitHeight: 60
        radius: 8

        // Two-tone gradient matching SMAHButton
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#16182080" }
            GradientStop { position: 1.0; color: "#12141c80" }
        }

        border.width: control.activeFocus ? 2 : 1
        border.color: control.activeFocus ? "#4a9eff" : "#ccc"

        // Hover overlay
        Rectangle {
            anchors.fill: parent
            radius: parent.radius
            color: "#ffffff"
            opacity: control.hovered ? 0.1 : 0

            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }
        }

        // Press effect
        scale: control.pressed ? 0.98 : 1.0

        Behavior on scale {
            NumberAnimation {
                duration: 100
                easing.type: Easing.OutCubic
            }
        }

        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }

        Behavior on border.width {
            NumberAnimation { duration: 200 }
        }
    }

    popup: Popup {
        y: control.height + 5
        width: control.width
        implicitHeight: popupHeight
        padding: 8

        // Smooth entrance animation
        enter: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.0
                to: 1.0
                duration: 200
                easing.type: Easing.OutCubic
            }
        }

        exit: Transition {
            NumberAnimation {
                property: "opacity"
                from: 1.0
                to: 0.0
                duration: 150
                easing.type: Easing.InCubic
            }
        }

        contentItem: ListView {
            id: list
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollBar.vertical: SMAHScrollBar { }
        }

        background: Rectangle {
            color: "#1a1c24"
            radius: 8
            border.color: "#4a9eff"
            border.width: 1

            // Drop shadow effect
            layer.enabled: true
            layer.effect: DropShadow {
                transparentBorder: true
                horizontalOffset: 0
                verticalOffset: 4
                radius: 12.0
                samples: 17
                color: "#80000000"
            }
        }
    }

    model: []
}