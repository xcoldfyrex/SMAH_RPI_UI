import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtMultimedia

import smah.configuration
import smah.configuration.ambient

import "."
import "qrc:/SMAHComponents"

Page {

    id: page
    x: 0
    SMAHBackground {}
    SMAHTBox {
        ColumnLayout {
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
                    text: qsTr("Ambient Playback")
                    font.pixelSize: Style.fontHeaderSize
                }
            }
            ListView {
                ScrollBar.vertical: SMAHScrollBar { }
                id: mediaListView
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
                                console.log("file:" + applicationDirPath + "/.smah/assets/" + configuration.getAmbientLoopConfigurations[index].mFile)
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
        }
    }

    MediaPlayer {
        id: playMusic
        loops: MediaPlayer.Infinite
        //source: "file:///home/lenny/Documents/ice.wav"
        audioOutput: AudioOutput {
            volume: slider.value
        }
    }

}
