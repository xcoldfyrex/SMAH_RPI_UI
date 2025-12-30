import QtQuick 2.12
import QtQuick.Controls 2.5
import smah.light 1.0
import smah.zone 1.0
import smah.sensor 1.0
import "."
import QtQuick.Window 2.3
import QtMultimedia 5.12

import "qrc:/SMAHComponents/"

ApplicationWindow {
    id: window
    visible: true
    width: 1920
    height: 1080
    minimumWidth: 1920
    maximumWidth: 1920
    minimumHeight: 1080
    maximumHeight: 1080
    title: qsTr("SMAH")
    objectName: "toolBar";
    color: "black"

    property int outsideIndex: 0

    signal saverActive()

    Connections {
        target: idleDetection
        function onUserActivity() {
            idleTimer.restart()
            window.hideSaver()
        }
    }

    Timer {
        id: idleTimer
        interval: 30000; running: true; repeat: false
        onTriggered: {
            viewer.hidePopup()
            window.showSaver()
        }
    }

    function hideSaver()
    {
        screenSaver.visible = false
        toolBar.visible = true
    }

    function showSaver()
    {
        toolBar.visible = false
        screenSaver.visible = true
        drawer.close()
    }

    header: Rectangle {
        z: 2000
        id: toolBar
        height: toolButton.implicitHeight
        width: parent.width
        color: "#000000"
        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                drawer.open()
            }
        }

        Label {
            font.pixelSize: 16
            color: "#ffffff"
            text: mainSwipeView.currentItem.title
            verticalAlignment: Text.AlignTop
            anchors.centerIn: parent
        }

        Clock {
            id: clock
            transformOrigin: Item.TopLeft
            anchors.bottom: parent.bottom
            //anchors.bottomMargin: 40
            anchors.right: parent.right
            //anchors.rightMargin: 50
            anchors.top: parent.top
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.25
        height: window.height
        font.family: "Tahoma"
        dim: true
        background: Rectangle{
            color: "#aa000000"
        }
        //SMAHMenu {
        //id: frame
        //width: drawer.width
        //height: drawer.height
        //color: "#6608111d"
        Column {
            anchors.fill: parent
            objectName: "mainMenu";
            id: mainMenu
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("Zones");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(3)
                    drawer.close()
                }
            }
            Label {
                text: "\t\n"
            }
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("Pond");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(4)
                    drawer.close()
                }
            }
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("Weather");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(0)
                    drawer.close()
                }
            }
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("Sensors");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(1)
                    drawer.close()
                }
            }
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("System");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(2)
                    drawer.close()
                }
            }
            SMAHMenuButton {
                SMAHLabel {
                    text: qsTr("Cameras");
                    font.pixelSize: 64
                }
                width: parent.width
                height: 64
                onClicked: {
                    mainSwipeView.setCurrentIndex(5)
                    drawer.close()
                }
            }

        }
    }
    /*
    function changeZone(index)
    {
        mainSwipeView.setCurrentIndex(index)
        drawer.close()
    }
*/
    SwipeView {
        id: mainSwipeView
        anchors.rightMargin: -222
        anchors.fill: parent
        interactive: false
        transitions: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }
        }
        Weather {}
        Sensors {}
        System { window: window }
        ViewUpstairs {
            id: viewer
            saverid: screenSaver
        }
        Pond {}
        Cameras {}
    }
    ScreenSaver {
        id: screenSaver
        Component.onCompleted: mainSwipeView.setCurrentIndex(2)
    }
}
