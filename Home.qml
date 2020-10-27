import QtQuick 2.0
import QtMultimedia 5.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Dialogs.qml 1.0

Page {
    id: page
    width: 1000
    height: 800
    title: "Home"
    SMAHBackground {}
    TabBar {
        id: bar
        width: 837
        height: 28
        TabButton {
            SMAHLabel {
                font.pixelSize: 20
                text: "Front Porch"
            }
        }

        TabButton {
            SMAHLabel {
                font.pixelSize: 20
                text:  "Back Porch"
            }
        }
    }
    StackLayout {
        id: stackLayout
        currentIndex: bar.currentIndex
        x: 0
        width: 837
        height: 549
        anchors.top: bar.bottom
        anchors.topMargin: 25

        Video {
            id: cam1Stream
            width: 640
            height: 480
            source: "rtsp://10.1.10.220/ch01/0"
            autoPlay: true
            opacity: 1.0
            fillMode: Image.Stretch
            muted: true
        }
        Video {
            id: cam2Stream
            width: 640
            height: 480
            source: "rtsp://10.1.10.221/h264"
            autoPlay: true
            opacity: 1.0
            fillMode: Image.Stretch
            muted: true
        }
    }
}

/*##^##
Designer {
    D{i:5;anchors_y:34}D{i:7;anchors_y:34}
}
##^##*/
