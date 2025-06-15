import QtQuick 2.12
import QtQuick.Controls 2.5
import smah.light 1.0
import smah.zone 1.0
import smah.sensor 1.0
import "."
import QtQuick.Window 2.3
import QtMultimedia 5.12

import "zoneManagement.js" as ZoneCreation

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

    property var outsideIndex: 0

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

    header: ToolBar {
        z: 2000
        id: toolBar
        padding: 0
        topPadding: 0
        contentHeight: toolButton.implicitHeight
        SMAHBackground {
            height: parent.height
        }

        // header at the very top of all pages
        Rectangle{
            //color: "#00000077"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#8043454E"
                }
                GradientStop {
                    position: 1
                    color: "#8043454E"
                }
            }
            border.width: 0
            anchors.fill: parent
        }

        ToolButton {
            id: toolButton
            background: Style.menubg
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

        SMAHMenu {
            id: frame
            width: drawer.width
            height: drawer.height
            //color: "#08111d"
            Column {
                anchors.fill: parent
                objectName: "mainMenu";
                id: mainMenu
                /*
                ItemDelegate {
                    SMAHLabel {
                        text: qsTr("Home");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        mainSwipeView.setCurrentIndex(0)
                        drawer.close()
                    }
                }
                */
                SMAHButton {
                    SMAHLabel {
                        text: qsTr("Weather");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        mainSwipeView.setCurrentIndex(0)
                        drawer.close()
                    }
                }
                SMAHButton {
                    SMAHLabel {
                        text: qsTr("Sensors");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        mainSwipeView.setCurrentIndex(1)
                        drawer.close()
                    }
                }
                SMAHButton {
                    SMAHLabel {
                        text: qsTr("System");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        mainSwipeView.setCurrentIndex(2)
                        drawer.close()
                    }
                }
                SMAHButton {
                    SMAHLabel {
                        text: qsTr("Up");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        mainSwipeView.setCurrentIndex(3)
                        drawer.close()
                    }
                }
                Label {
                    text: "\t\n"
                }
            }
        }
    }

    function changeZone(index)
    {
        mainSwipeView.setCurrentIndex(index)
        drawer.close()
    }

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
        ViewUpstairs { }
        Component.onCompleted: {         
            //mainSwipeView.setCurrentIndex(0)
            var offset = mainSwipeView.count
            for (var i=0; i<zoneList.length; i++) {
                ZoneCreation.zoneLightList[zoneList[i].getName] = zoneList[i].getLightList
                //if (zoneList[i].getLightList > 0) {

                var component = Qt.createComponent("ZoneItem.qml")
                var loadwin = component.createObject(mainMenu, {id: i, zoneName: zoneList[i].getName, drawerID: "zoneDrawer" + i, lights: zoneList[i].getLightList, index: i+offset })
                var zonecomponent= Qt.createComponent("ZoneOptions.qml")
                var zoneloadwin = zonecomponent.createObject(mainMenu, {zoneName: zoneList[i].getName, lights: zoneList[i].getLightList} )
                ZoneCreation.zoneFunctions[zoneList[i].getName] = zoneloadwin
                mainSwipeView.insertItem(i+offset, zoneloadwin)
                //}
            }
        }

    }
    SMAHBackground {}
    ScreenSaver {
        id: screenSaver
    }
}


/*##^##
Designer {
    D{i:8;anchors_height:42;anchors_width:1280}
}
##^##*/
