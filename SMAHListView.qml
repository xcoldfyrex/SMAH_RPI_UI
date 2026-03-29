import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material

import ".."

ListView {
    id: listView
    clip: true
    focus: true

    // Touch-friendly spacing
    spacing: 2

    // Smooth scrolling behavior
    boundsBehavior: Flickable.StopAtBounds

    // Scroll indicator
    ScrollBar.vertical: SMAHScrollBar { }

    // Default delegate with SMAH styling
    delegate: ItemDelegate {
        width: listView.width
        height: 50

        contentItem: Text {
            text: modelData
            color: "white"
            font.pointSize: Style.fontCellSize
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        background: Rectangle {
            implicitHeight: 50
            color: {
                if (parent.pressed) return "#0d0f15"
                if (parent.hovered) return Qt.rgba(1, 1, 1, 0.05)
                return "transparent"
            }

            // Subtle border between items
            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: 1
                color: Qt.rgba(1, 1, 1, 0.08)
            }

            // Hover effect overlay
            Rectangle {
                anchors.fill: parent
                color: "white"
                opacity: parent.parent.hovered ? 0.03 : 0

                Behavior on opacity {
                    NumberAnimation { duration: 150 }
                }
            }

            // Press animation
            scale: parent.pressed ? 0.98 : 1.0

            Behavior on scale {
                NumberAnimation { duration: 100 }
            }

            Behavior on color {
                ColorAnimation { duration: 150 }
            }
        }
    }

    // Highlight styling (matches SMAHComboBox)
    highlight: Rectangle {
        color: "#12141C"
        radius: 5

        // Subtle border for focus state
        border.width: 2
        border.color: listView.activeFocus ? "#4a9eff" : "#2a2d38"

        // Gradient effect
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(0.09, 0.1, 0.13, 0.8) }
            GradientStop { position: 1.0; color: Qt.rgba(0.07, 0.08, 0.11, 0.9) }
        }

        Behavior on border.color {
            ColorAnimation { duration: 200 }
        }
    }

    highlightFollowsCurrentItem: true
    highlightMoveDuration: 200
}