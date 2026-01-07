import QtQuick 2.0

import QtQuick.Controls
import QtQuick.Layouts
import smah.zone
import smah.light
import smah.scene

import ".."
import "qrc:/SMAHComponents/"

Item {
    property date timeout: new Date(9999,9,9);
    property Light device
    property var parentObject
    property Zone zone

    id: timerontrolPage
    implicitWidth: parent.width
    implicitHeight: parent.height
    GridLayout {
        id: layout
        //implicitWidth: parent.width
        implicitHeight: 500
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: parent.left
        }
        rows: 8
        SMAHLabel {
            Layout.row: 0
            Layout.column: 0
            text: "Seconds"
            font.pixelSize: Style.fontCellSize
        }

        SMAHLabel {
            Layout.row: 0
            Layout.column: 1
            text: "Minutes"
            font.pixelSize: Style.fontCellSize
        }

        SMAHLabel {
            Layout.row: 0
            Layout.column: 2
            text: "Hours"
            font.pixelSize: Style.fontCellSize
        }

        SMAHLabel {
            Layout.row: 0
            Layout.column: 3
            text: "Timer Action"
            font.pixelSize: Style.fontCellSize
        }

        SMAHLabel {
            Layout.row: 2
            Layout.column: 0
            text: "Transition Duration"
            font.pixelSize: Style.fontCellSize
        }

        SMAHComboBox  {
            Layout.row: 1
            Layout.column: 0
            id: secondsBox
            popupHeight: timerontrolPage.implicitHeight - 50
            model: Array.from(Array(60).keys())
        }

        SMAHComboBox  {
            Layout.row: 1
            Layout.column: 1
            id: minutesBox
            popupHeight: timerontrolPage.implicitHeight - 50
            model: Array.from(Array(60).keys())
        }

        SMAHComboBox  {
            Layout.row: 1
            Layout.column: 2
            id: hoursBox
            popupHeight: timerontrolPage.implicitHeight - 50
            model: Array.from(Array(25).keys())
        }

        SMAHComboBox  {
            Layout.row: 1
            Layout.column: 3
            id: actionBox
            popupHeight: timerontrolPage.implicitHeight - 50
            model: ["Off", "On", "Toggle"]
        }

        SMAHComboBox  {
            Layout.row: 3
            Layout.column: 0
            id: transitionBox
            popupHeight: timerontrolPage.implicitHeight - 50
            //model: [Array.from(Array(31).keys())]
            model: [0, 10, 15, 20, 25, 30, 45, 60]
        }

        /* just a spacer */
        Item {
            Layout.fillWidth: true
            Layout.row: 1
            Layout.column: 5
        }

        SMAHButton {
            id: startb
            text: "Start"
            onClicked: {
                timerontrolPage.timeout = new Date(Date.now() + (((secondsBox.currentValue) + (minutesBox.currentValue * 60) + (hoursBox.currentValue * 60 * 60)) * 1000));
                sleeperTimer.restart()
            }
            Layout.alignment: Qt.AlignBottom || Qt.AlignLeft
            Layout.row: 1
            Layout.column: 6
        }

        /* just a spacer */
        Item {
            Layout.fillHeight: true
            Layout.row: 4
            Layout.column: 0
        }
        SMAHButton {
            id: closeb
            text: "Close"
            onClicked: {
                timerontrolPage.visible = false
                element.text = zone.getName
                parentObject.visible = true
            }
            Layout.alignment: Qt.AlignBottom || Qt.AlignLeft
            Layout.row: 6
            Layout.column: 0
        }


        SMAHLabel {
            id: lightState
            Layout.row: 5
            Layout.column: 6
            text: device.getState + " " + device.getBrightness
            font.pixelSize: Style.fontColumnHeaderSize
        }

        SMAHLabel {
            id: countdown
            Layout.row: 6
            Layout.column: 6
            text: "Stopped"
            font.pixelSize: Style.fontColumnHeaderSize
        }


        Timer {
            id: transitionTimer
            interval: 100; running: false; repeat: true;
            onTriggered:  {
                if (device.getBrightness === 1 && actionBox.currentValue === "Off" )
                {
                    device.setState(0)
                    transitionTimer.stop()
                }
                else if (actionBox.currentValue === "Off")
                {
                    device.setBrightness(device.getBrightness - 1)
                }
                else if (device.getBrightness === 100 && actionBox.currentValue === "On" )
                {
                    transitionTimer.stop()
                }
                else if (actionBox.currentValue === "On")
                {
                    device.setBrightness(device.getBrightness + 1)
                }

            }
        }

        Timer {
            id: sleeperTimer
            interval: 100; running: false; repeat: true;

            onTriggered: {
                var now = new Date(Date.now()).getTime();
                countdown.text = parseMillisecondsIntoReadableTime((timerontrolPage.timeout.getTime() - now) + 1000)
                if (now >= timerontrolPage.timeout.getTime()) {
                    // make sure we are not already in a target state
                    countdown.text = "Stopped"
                    sleeperTimer.stop()
                    if (device.getState === false && actionBox.currentValue === "Off") {
                        transitionTimer.stop()
                        return
                    }

                    // choose the correct actions now
                    var timerinterval
                    if (actionBox.currentValue === "On")
                        //device must be on for dimmer to work
                        device.setState(1)
                        if (transitionBox.currentValue !== 0)
                        {
                            timerinterval = (transitionBox.currentValue / 100 ) * 1000
                            transitionTimer.interval = timerinterval
                            transitionTimer.start()
                        }

                    if (actionBox.currentValue === "Off")
                        if (transitionBox.currentValue !== 0)
                        {
                            timerinterval = (transitionBox.currentValue / device.getBrightness ) * 1000
                            transitionTimer.interval = timerinterval
                            transitionTimer.start()
                        }
                        else
                        {
                            device.setState(0)
                        }
                    if (actionBox.currentValue === "Toggle")
                        device.toggleState()

                }
            }
        }
    }
    function parseMillisecondsIntoReadableTime(milliseconds){
        //Get hours from milliseconds
        var hours = milliseconds / (1000*60*60);
        var absoluteHours = Math.floor(hours);
        var h = absoluteHours > 9 ? absoluteHours : '0' + absoluteHours;

        //Get remainder from hours and convert to minutes
        var minutes = (hours - absoluteHours) * 60;
        var absoluteMinutes = Math.floor(minutes);
        var m = absoluteMinutes > 9 ? absoluteMinutes : '0' +  absoluteMinutes;

        //Get remainder from minutes and convert to seconds
        var seconds = (minutes - absoluteMinutes) * 60;
        var absoluteSeconds = Math.floor(seconds);
        var s = absoluteSeconds > 9 ? absoluteSeconds : '0' + absoluteSeconds;

        return h + ':' + m + ':' + s;
    }
}

