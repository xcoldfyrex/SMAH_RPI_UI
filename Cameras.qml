import QtQuick 2.4
import QtQuick.Controls
import QtQuick.Layouts

import QtMultimedia

import smah.camera

Page {
    Component.onCompleted: {
        console.log(factory.getCameraObjects().length)
    }

    ListView {
        model: factory.getCameraObjects()
        anchors.fill: parent
        delegate: Component {
            Item {
                Label {
                    text: "sdfds"
                }

                MediaPlayer {
                    id: player1
                    source: factory.getCameraObjects()[index].getSettings.low
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
