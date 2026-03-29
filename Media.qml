import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtMultimedia

import smah.configuration

import "."
import "qrc:/SMAHComponents"

Item {
    property date timeout: new Date(9999,9,9);
    id: page
    x: 0
    SMAHTBox {
        headerText: "Media"
        SMAHHeader {
            id: header1
            y: 0
            width: 600
            Layout.alignment: Qt.AlignCenter
            Text {
                id: element
                color: "#ffffff"
                text: qsTr("Ambient Playback")
                font.pixelSize: Style.fontHeaderSize
            }
        }
        ListView {
            ScrollBar.vertical: SMAHScrollBar { }
            id: mediaListView
            anchors.top: header1.bottom
            width: 300
            height: 400
            boundsBehavior: Flickable.StopAtBounds
            Layout.fillWidth: true
            Layout.fillHeight: false
            highlightMoveDuration: 200
            highlightMoveVelocity: -1
            clip: true
            highlight: Rectangle {
                color: '#666666'
                width: 300
                Text {
                    anchors.centerIn: parent
                    color: 'white'
                }
            }
            model: configuration.getAmbientLoopConfigurations
            focus: true
            delegate: Component {
                Item {
                    height: 35
                    width: 300
                    Row {
                        width: parent.width
                        Text {
                            color: "#fefdfd"
                            text: configuration.getAmbientLoopConfigurations[index].mName
                            font.pixelSize: 32
                            width: 300

                        }

                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            mediaListView.currentIndex = index
                            playMusic.source = "file:" + applicationDirPath + "/.smah/assets/" + configuration.getAmbientLoopConfigurations[index].mFile
                            playMusic.play()
                        }
                    }

                }
            }
        }

        SMAHButton {
            id: play
            anchors {
                top: mediaListView.top
                left: mediaListView.right
            }
            text: "PLAY"
            onClicked: {
                playMusic.play()
            }
        }

        SMAHButton {
            id: stop
            anchors {
                top: play.bottom
                left: mediaListView.right
            }
            text: "STOP"
            onClicked: {
                playMusic.stop()
            }
        }

        Slider {
            anchors {
                top: mediaListView.bottom
                left: mediaListView.left
            }
            id: slider
            from: 0.
            to: 1.
            height: 100
            width: 200
            handle: Rectangle {
                id: handleId
                x: slider.visualPosition * (slider.width - width)
                y: (slider.height - height) / 2
                width: 15
                height: slider.height
                color: "#12141C"
            }
            background: Rectangle {
                y: (slider.height - height) / 2
                height: 20
                color: "#ccc"

                Rectangle {
                    width: slider.visualPosition * parent.width
                    height: parent.height
                    color: "#777"
                }
            }
        }
        SMAHLabel {
            text: "Play timer: "
            id: playTimerLabel
            anchors {
                top: parent.top
                left: minutesBox.left
            }
            font.pixelSize: Style.fontColumnHeaderSize
        }

        SMAHLabel {
            id: countdown
            anchors {
                top: parent.top
                left: playTimerLabel.right
            }
            text: "Stopped"
            font.pixelSize: Style.fontColumnHeaderSize
        }

        SMAHLabel {
            id: minuteLabel
            anchors {
                top: playTimerLabel.bottom
                left: minutesBox.left
            }
            text: "Minutes"
            font.pixelSize: Style.fontCellSize
        }

        SMAHLabel {
            id: hourLabel
            anchors {
                top: playTimerLabel.bottom
                left: hoursBox.left
            }
            text: "Hours"
            font.pixelSize: Style.fontCellSize
        }

        SMAHComboBox  {
            anchors {
                top: minuteLabel.bottom
                right: hoursBox.left
            }
            id: minutesBox
            popupHeight: 700
            model: Array.from(Array(60).keys())
        }

        SMAHComboBox  {
            anchors {
                top: hourLabel.bottom
                right: parent.right
            }
            id: hoursBox
            popupHeight: 700
            model: Array.from(Array(25).keys())
        }

        SMAHButton {
            id: timerStart
            anchors {
                top: minutesBox.bottom
                left: minutesBox.left
            }
            text: "Start Timer"
            onClicked: {
                page.timeout = new Date(Date.now() + ((minutesBox.currentValue * 60) + (hoursBox.currentValue * 60 * 60)) * 1000);
                sleeperTimer.restart()
            }
        }
    }

    Timer {
        id: sleeperTimer
        interval: 100; running: false; repeat: true;
        onTriggered: {
            var now = new Date(Date.now()).getTime();
            countdown.text = parseMillisecondsIntoReadableTime((page.timeout.getTime() - now) + 1000)
            if (now >= page.timeout.getTime()) {
                countdown.text = "Stopped"
                sleeperTimer.stop()
                playMusic.stop()
            }
        }
    }

    MediaPlayer {
        id: playMusic
        loops: MediaPlayer.Infinite
        audioOutput: AudioOutput {
            volume: slider.value
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


