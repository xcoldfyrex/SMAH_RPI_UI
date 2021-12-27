import QtQuick 2.0
import QtMultimedia 5.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13

Page {
    SMAHBackground {}
    TabBar {
        background: Rectangle {
            radius: 4
        }
        id: bar
        width: 837
        height: 28
        SMAHTabButton {
            anchors.top: parent.top
            height: parent.height
            SMAHLabel {
                font.pixelSize: 20
                color: "black"
                text: "Front Porch"
            }
        }

        SMAHTabButton {
            anchors.top: parent.top
            height: parent.height
            SMAHLabel {
                font.pixelSize: 20
                color: "black"
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
/*
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
        */
    }

}
