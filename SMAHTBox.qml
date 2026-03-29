import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Effects

Item {
    id: root

    // Configurable properties
    property string headerText: "Page Title"
    property int headerFontSize: 28
    property int headerHeight: 80
    property alias contentArea: contentArea

    // Responsive sizing - 90% of window dimensions
    implicitWidth: window.width * 0.9
    implicitHeight: window.height * 0.9

    x: window.width / 2 - width / 2
    y: window.height / 2 - height / 2

    // Center in parent
    anchors.centerIn: parent

    // Default property - children go into contentArea
    default property alias content: contentArea.data

    // Main container with glassmorphic effect
    Rectangle {
        id: glassContainer
        anchors.fill: parent
        anchors.margins: 0

        color: "#dd000000"  // Semi-transparent black
        radius: 24  // Modern, softer corner radius

        // Subtle inner shadow effect
        layer.enabled: true
        layer.effect: MultiEffect {
            shadowEnabled: true
            shadowColor: "#80000000"
            shadowBlur: 0.4
            shadowHorizontalOffset: 0
            shadowVerticalOffset: 4
        }

        // Modern header component
        Rectangle {
            id: headerContainer
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 0
            height: root.headerHeight
            color: "transparent"

            // Gradient background using modern approach
            Rectangle {
                id: headerBackground
                anchors.fill: parent
                color: "transparent"

                // Horizontal gradient effect
                Rectangle {
                    anchors.fill: parent
                    rotation: 0

                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color: "#00000000" }
                        GradientStop { position: 0.5; color: "#40000000" }
                        GradientStop { position: 1.0; color: "#ff000000" }
                    }
                }
            }

            // Header text
            Label {
                id: headerLabel
                anchors.centerIn: parent
                text: root.headerText
                color: "#ffffff"
                font.pixelSize: root.headerFontSize
                font.weight: Font.Medium

                // Text shadow for better readability
                layer.enabled: true
                layer.effect: MultiEffect {
                    shadowEnabled: true
                    shadowColor: "#80000000"
                    shadowBlur: 0.3
                    shadowHorizontalOffset: 0
                    shadowVerticalOffset: 2
                }
            }

            // Subtle bottom separator
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                opacity: 0.2

                gradient: Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: "#00ffffff" }
                    GradientStop { position: 0.5; color: "#ffffffff" }
                    GradientStop { position: 1.0; color: "#00ffffff" }
                }
            }
        }

        // Content area for child items
        Item {
            id: contentArea
            anchors.top: headerContainer.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 40  // Comfortable padding
            anchors.topMargin: 20  // Less margin after header
        }
    }
}
