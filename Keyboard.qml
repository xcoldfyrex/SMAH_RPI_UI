import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import "qrc:/SMAHComponents"

Rectangle {
    id: keyboardOverlay
    x: 0
    y: 0
    width: 1920
    height: 1080
    //anchors.fill: parent
    //anchors.centerIn: parent
    color: "#80000000" // Semi-transparent black
    z: 100 // Ensure it's on top
    property bool shiftPressed: false  // Track shift state

    // Close overlay when clicking outside keyboard
    MouseArea {
        anchors.fill: parent
        onClicked: keyboardOverlay.visible = false
    }

    // Keyboard container
    Rectangle {
        id: keyboardContainer
        anchors.centerIn: parent
        width: Math.min(parent.width * 0.6)
        height: Math.min(parent.height * 0.5)
        color: "#111111"
        border.color: "#444444"
        border.width: 1

        // Prevent clicks from passing through to overlay
        MouseArea {
            anchors.fill: parent
            onClicked: {} // Consume clicks
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 15

            // Text input display
            TextField {
                id: textInput
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                font.pixelSize: 18
                placeholderText: ""
                selectByMouse: true
                focus: true

                // Handle physical keyboard enter key
                Keys.onReturnPressed: submitInput()
                Keys.onEnterPressed: submitInput()

                background: Rectangle {
                    color: "#000000"
                    border.color: textInput.activeFocus ? "#0078d4" : "#cccccc"
                    border.width: 2
                    radius: 5
                }
            }

            // Virtual keyboard
            GridLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                columns: 10
                rowSpacing: 8
                columnSpacing: 8

                // Row 1: Numbers
                Repeater {
                    model: ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]
                    SMAHButton {
                        implicitWidth: 100
                        text: modelData
                        onClicked: textInput.text += text
                    }
                }

                // Row 2: QWERTYUIOP
                Repeater {
                    model: ["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"]
                    SMAHButton {
                        implicitWidth: 100
                        text: keyboardOverlay.shiftPressed ? modelData : modelData.toLowerCase()
                        onClicked: {
                            textInput.text += text
                            keyboardOverlay.shiftPressed = false  // Auto-release shift after typing
                        }
                    }
                }

                // Row 3: ASDFGHJKL + spacer
                Item { Layout.preferredWidth: 20 } // Left spacer
                Repeater {
                    model: ["A", "S", "D", "F", "G", "H", "J", "K", "L"]
                    SMAHButton {
                        implicitWidth: 100
                        text: keyboardOverlay.shiftPressed ? modelData : modelData.toLowerCase()
                        onClicked: {
                            textInput.text += text
                            keyboardOverlay.shiftPressed = false  // Auto-release shift after typing
                        }
                    }
                }

                // Row 4: ZXCVBNM + spacers
                Item { Layout.preferredWidth: 40 } // Left spacer
                Repeater {
                    model: ["Z", "X", "C", "V", "B", "N", "M"]
                    SMAHButton {
                        implicitWidth: 100
                        text: keyboardOverlay.shiftPressed ? modelData : modelData.toLowerCase()
                        onClicked: textInput.text += text
                    }
                }
                Item { Layout.preferredWidth: 40 } // Right spacer
                Item { Layout.preferredWidth: 20 } // Extra spacer

                // Row 5: Special keys
                SMAHButton {
                    Layout.fillWidth: true
                    implicitWidth: 100
                    text: "Shift"
                    onClicked: keyboardOverlay.shiftPressed = !keyboardOverlay.shiftPressed
                }
                Item { Layout.preferredWidth: 40 } // Extra spacer

                SMAHButton {
                    Layout.columnSpan: 6
                    implicitWidth: 500
                    text: "Space"
                    onClicked: textInput.text += " "
                }

                Item {  Layout.preferredWidth: 40} // Extra spacer

                SMAHButton {
                    Layout.columnSpan: 1
                    Layout.fillWidth: true
                    text: "Backspace"
                    onClicked: {
                        if (textInput.text.length > 0) {
                            textInput.text = textInput.text.slice(0, -1)
                        }
                    }
                }

                //Row 6
                Item { Layout.preferredWidth: 80 } // Extra spacer

                SMAHButton {
                    Layout.columnSpan: 4
                    implicitWidth: 300
                    Layout.fillWidth: true
                    text: "OK"
                    onClicked: submitInput()
                }
                Item { Layout.preferredWidth: 80 } // Extra spacer

                SMAHButton {
                    Layout.columnSpan: 4
                    implicitWidth: 300

                    text: "Cancel"
                    onClicked: {
                        textInput.text = ""
                        keyboardOverlay.visible = false
                    }
                }
            }
        }
    }
    // Function to submit input and close keyboard
    function submitInput() {
        if (textInput.text.trim().length > 0) {
            addActionSetConfigurations(textInput.text)
            textInput.text = "" // Clear input
            keyboardOverlay.visible = false // Hide keyboard
        }
    }

    // Your existing function (placeholder implementation)
    function addActionSetConfigurations(input) {
        console.log("addActionSetConfigurations called with:", input)
        // Add your actual implementation here
    }
}