import QtQuick 2.4
import QtQuick.Controls
import QtQuick.Layouts

import QtMultimedia

import smah.camera

Page {
    ListView {
        model: cameraList
        anchors.fill: parent
        delegate: Component {
            Item {
                MediaPlayer {
                    id: player1
                    source: cameraList[index].getSettings.low
                    videoOutput: videoOutput1

                    onErrorOccurred: {
                        console.log(player1.errorString)
                        console.log(player1.mediaStatus)
                    }

                    onPlaybackStateChanged: {
                        console.log(player1.mediaStatus)
                        player1.play()
                    }

                    onPlayingChanged: {
                        console.log(player1.mediaStatus)
                    }

                    Component.onCompleted: {player1.play()}
                }

                VideoOutput {
                    id: videoOutput1
                    Layout.fillHeight: true
                }
            }
        }
    }
}
