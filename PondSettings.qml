import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.ponddata
import QtMultimedia
import QtCharts
import smah.configuration
import QtQuick.Controls.Material

import "."
import "qrc:/SMAHComponents"

Page {
    property var pHReadings: []  // Array to store last 20 readings
    property int maxReadings: 40
    property real averageVoltage: 0.0
    property real testpH: 0.0

    // Calibration values (these would ideally be initialized from C++)
    property real calibrationLow: configuration.getPondItemConfigurations()[0].mLowPHCal
    property real calibrationMid: configuration.getPondItemConfigurations()[0].mMidPHCal
    property real calibrationHigh: configuration.getPondItemConfigurations()[0].mHighPHCal

    // New calibration values being set
    property real newCalibrationLow: calibrationLow
    property real newCalibrationMid: calibrationMid
    property real newCalibrationHigh: calibrationHigh

    // Monitor pH changes from C++ and update rolling average
    Connections {
        target: ponddataitems[0]  // Your C++ object
        function onUpdatedPH() {
            // Add new reading
            pHReadings.push(ponddataitems[0].raw_mV)

            // Keep only last 20 readings
            if (pHReadings.length > maxReadings) {
                pHReadings.shift()
            }
            pHReadings = pHReadings.slice()
            // Calculate average
            var sum = 0.0
            for (var i = 0; i < pHReadings.length; i++) {
                sum += pHReadings[i]
            }
            averageVoltage = pHReadings.length > 0 ? sum / pHReadings.length : 0.0
            calcPh()
        }
    }
    function resetPH() {
        pHReadings = []
        pHReadings = pHReadings.slice()
    }

    function calcPh() {
            if (ponddataitems[0].raw_mV > calibrationMid) { //high voltage = low ph
                testpH = 7.0 - 3.0 / (calibrationLow - calibrationMid) * (ponddataitems[0].raw_mV - calibrationMid);
            } else {
                testpH = 7.0 - 3.0 / (calibrationMid - calibrationHigh) * (ponddataitems[0].raw_mV - calibrationMid);
            }
    }

    id: calibrationPage
    visible: true
    x: 0
    SMAHBackground {}
    SMAHTBox {
        ColumnLayout {
            id: realTimeData
            Layout.fillWidth: true
            Layout.fillHeight: true
            SMAHHeader {
                id: header1
                y: 0
                width: 600
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: element
                    color: "#ffffff"
                    text: qsTr("Pond Calibrations")
                    font.pixelSize: Style.fontHeaderSize
                }
            }
            ColumnLayout {
                //anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                // Current Average Display
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 200
                    color: "#aa000000"
                    ColumnLayout {
                        anchors.centerIn: parent
                        spacing: 5

                        SMAHLabel {
                            text: "Current Average Voltage (last 40 readings)"
                            font.pixelSize: Style.fontCellSize
                        }

                        SMAHLabel {
                            text: averageVoltage.toFixed(3)
                            font.pixelSize: Style.fontHeaderSize
                            font.bold: true
                            color: "#2196F3"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        SMAHLabel {
                            text: "Readings: " + pHReadings.length + "/" + maxReadings
                            font.pixelSize: Style.fontSmallSize
                            color: "white"
                            Layout.alignment: Qt.AlignHCenter
                        }

                        SMAHLabel {
                            text: "Calibrated pH"
                            font.pixelSize: Style.fontCellSize
                        }

                        SMAHLabel {
                            text: testpH.toFixed(3)
                            font.pixelSize: Style.fontHeaderSize
                            font.bold: true
                            color: "#2196F3"
                            Layout.alignment: Qt.AlignHCenter
                        }
                    }
                }

                // Calibration Points Section
                GroupBox {
                    Layout.fillWidth: true
                    font.bold: false

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 15

                        // Low pH Calibration
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            SMAHLabel {
                                text: "Low pH:"
                                font.pixelSize: 14
                                Layout.preferredWidth: 80
                            }

                            Label {
                                text: calibrationLow.toFixed(2)
                                font.pixelSize: 16
                                font.bold: true
                                color: "#FF5722"
                                Layout.preferredWidth: 80
                            }

                            SMAHButton {
                                text: "Set to Current"
                                Layout.fillWidth: true
                                onClicked: {
                                    calibrationLow = ponddataitems[0].raw_mV
                                    newCalibrationLow = ponddataitems[0].raw_mV
                                    lowSetIndicator.visible = true
                                    lowSetTimer.restart()
                                    resetPH()
                                }
                            }

                            Label {
                                id: lowSetIndicator
                                text: "✓ Set to " + newCalibrationLow.toFixed(3)
                                color: "#4CAF50"
                                font.pixelSize: 12
                                visible: false
                            }

                            Timer {
                                id: lowSetTimer
                                interval: 3000
                                onTriggered: lowSetIndicator.visible = false
                            }
                        }

                        // Mid pH Calibration
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            SMAHLabel {
                                text: "Mid pH:"
                                font.pixelSize: 14
                                Layout.preferredWidth: 80
                            }

                            Label {
                                text: calibrationMid.toFixed(2)
                                font.pixelSize: 16
                                font.bold: true
                                color: "#FFC107"
                                Layout.preferredWidth: 80
                            }

                            SMAHButton {
                                text: "Set to Current"
                                Layout.fillWidth: true
                                onClicked: {
                                    calibrationMid = ponddataitems[0].raw_mV
                                    newCalibrationMid = ponddataitems[0].raw_mV
                                    midSetIndicator.visible = true
                                    midSetTimer.restart()
                                    resetPH()
                                }
                            }

                            Label {
                                id: midSetIndicator
                                text: "✓ Set to " + newCalibrationMid.toFixed(3)
                                color: "#4CAF50"
                                font.pixelSize: 12
                                visible: false
                            }

                            Timer {
                                id: midSetTimer
                                interval: 3000
                                onTriggered: midSetIndicator.visible = false
                            }
                        }

                        // High pH Calibration
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            SMAHLabel {
                                text: "High pH:"
                                font.pixelSize: 14
                                Layout.preferredWidth: 80
                            }

                            Label {
                                text: calibrationHigh.toFixed(2)
                                font.pixelSize: 16
                                font.bold: true
                                color: "#9C27B0"
                                Layout.preferredWidth: 80
                            }

                            SMAHButton {
                                text: "Set to Current"
                                Layout.fillWidth: true
                                onClicked: {
                                    calibrationHigh = ponddataitems[0].raw_mV
                                    newCalibrationHigh = ponddataitems[0].raw_mV
                                    highSetIndicator.visible = true
                                    highSetTimer.restart()
                                    resetPH()
                                }
                            }

                            Label {
                                id: highSetIndicator
                                text: "✓ Set to " + newCalibrationHigh.toFixed(3)
                                color: "#4CAF50"
                                font.pixelSize: 12
                                visible: false
                            }

                            Timer {
                                id: highSetTimer
                                interval: 3000
                                onTriggered: highSetIndicator.visible = false
                            }
                        }
                    }
                }

                // Spacer
                Item {
                    Layout.fillHeight: true
                }
                SMAHButton {
                    id: enterButton
                    text: "Enter Calibration Mode"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    onClicked: {
                        ponddataitems[0].setCalibrateMode(true)
                        saveButton.visible = true
                        visible = false
                        exitButton.visible = true
                    }
                }
                SMAHButton {
                    id: exitButton
                    visible: false
                    text: "Exit Calibration Mode"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    onClicked: {
                        ponddataitems[0].setCalibrateMode(false)
                        saveButton.visible = false
                        visible = false
                        enterButton.visible = true
                    }
                }
                // Save Button
                SMAHButton {
                    id: saveButton
                    visible: false
                    text: "Save Calibration"
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    highlighted: true

                    onClicked: {
                        // Call C++ method to save calibrations
                        configuration.updatePHCalibrations(newCalibrationLow, newCalibrationMid, newCalibrationHigh)
                        configuration.savePondItemConfigurations()

                        // Update the displayed calibration values
                        calibrationLow = newCalibrationLow
                        calibrationMid = newCalibrationMid
                        calibrationHigh = newCalibrationHigh

                        // Show confirmation
                        saveConfirmation.open()

                        ponddataitems[0].setCalibrateMode(false)
                        visible = false
                        enterButton.visible = true
                        exitButton.visible = false
                    }
                }
            }

            ColumnLayout {
                SMAHLabel {
                    text: "Recent readings:"
                    color: "white"
                    font.pixelSize: Style.fontCellSize
                }

                ListView {
                    id: readingsList
                    width: 300
                    implicitHeight: 400
                    Layout.fillHeight: true
                    model: pHReadings.reverse()
                    delegate: Component {
                        Item {
                            height: 20
                            width: readingsList.width
                            SMAHLabel {
                                text: modelData
                            }
                        }
                    }
                }
            }

            // Save Confirmation Dialog
            Dialog {
                id: saveConfirmation
                title: "Calibration Saved"
                modal: true
                anchors.centerIn: parent
                standardButtons: Dialog.Ok

                Label {
                    text: "New calibration values have been saved:\n" +
                          "Low: " + calibrationLow.toFixed(3) + "\n" +
                          "Mid: " + calibrationMid.toFixed(3) + "\n" +
                          "High: " + calibrationHigh.toFixed(3)
                }
            }
        }
    }
}