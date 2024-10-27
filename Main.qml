import QtQuick 2.12
import QtQuick.Controls 2.5
import smah.light 1.0
import smah.zone 1.0
import smah.sensor 1.0

import QtQuick.Window 2.3
import QtMultimedia 5.12

import "zoneManagement.js" as ZoneCreation

ApplicationWindow {
    id: window
    visible: true
    width: 1280
    height: 800
    minimumWidth: 1280
    maximumWidth: 1280
    minimumHeight: 800
    maximumHeight: 800
    title: qsTr("SMAH")
    objectName: "toolBar";
    color: "black"

    property var outsideIndex: 0

    Connections {
        target: idleDetection
        function onUserActivity() {
            idleTimer.restart()
            hideSaver()
        }
    }

    Timer {
        id: idleTimer
        interval: 30000; running: true; repeat: false
        onTriggered: {
            showSaver()
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
        Rectangle{
            //color: "#00000077"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#80000000"
                }
                GradientStop {
                    position: 1
                    color: "#8008111d"
                }
            }
            border.width: 0
            anchors.fill: parent
        }

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
            text: stackView.currentItem.title
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
        Rectangle {
            width: drawer.width
            height: drawer.height
            color: "#08111d"
            Column {
                anchors.fill: parent
                objectName: "mainMenu";
                id: mainMenu

                ItemDelegate {
                    SMAHLabel {
                        text: qsTr("Home");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        stackView.setCurrentIndex(0)
                        drawer.close()
                    }
                }
                ItemDelegate {
                    SMAHLabel {
                        text: qsTr("Weather");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        stackView.setCurrentIndex(1)
                        drawer.close()
                    }
                }
                ItemDelegate {
                    SMAHLabel {
                        text: qsTr("System");
                        font.pixelSize: 40
                    }
                    width: parent.width
                    height: 40
                    onClicked: {
                        stackView.setCurrentIndex(2)
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
        stackView.setCurrentIndex(index)
        drawer.close()
    }

    SwipeView {
        id: stackView
        anchors.rightMargin: -222
        anchors.fill: parent
        interactive: false
        transitions: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }
            }

        Home { }
        Weather { }
        System { }
        Component.onCompleted: {
            var offset = stackView.count
            for (var i=0; i<zoneList.length; i++) {
                ZoneCreation.zoneLightList[zoneList[i].getName] = zoneList[i].getLightList
                var component = Qt.createComponent("ZoneItem.qml")
                var loadwin = component.createObject(mainMenu, {id: i, zoneName: zoneList[i].getName, drawerID: "zoneDrawer" + i, lights: zoneList[i].getLightList, index: i+offset })
                var zonecomponent= Qt.createComponent("ZoneOptions.qml")
                var zoneloadwin = zonecomponent.createObject(mainMenu, {zoneName: zoneList[i].getName, lights: zoneList[i].getLightList} )
                ZoneCreation.zoneFunctions[zoneList[i].getName] = zoneloadwin
                stackView.insertItem(i+offset, zoneloadwin)
            }
        }
    }
    SMAHBackground {}

    Rectangle {
        id: screenSaver
        width: parent.width
        height: parent.height
        color: "black"
        Component.onCompleted: {
            showSaver()
            for (var i=0; i<sensorList.length; i++)
            {
                if (sensorList[i].name === "Outside")
                {
                    outsideIndex = i
                }
            }
        }
        Timer {
            interval: 100; running: true; repeat: true;
            onTriggered: {
                var ts = Qt.formatTime(new Date(),"hh:mm:ss")
                timeText.text = ts
            }
        }
        Text {
            id: timeText
            //fontSizeMode: Text.Fit
            elide: Text.ElideRight
            horizontalAlignment: Text.Center
            verticalAlignment: Text.Center
            color: "#454545"
            font.family: "Helvetica"
            font.bold: true; font.pixelSize: 256
            style: Text.Raised; styleColor: "#757575"
        }
        Text {
            id: temperature
            text: sensorList[outsideIndex].temperature.toFixed(1) + "F\n" + sensorList[outsideIndex].rh + "%"
            elide: Text.ElideLeft
            horizontalAlignment: Text.Right
            //verticalAlignment: Text.Center
            anchors.bottom: parent.bottom
            color: "#454545"
            font.family: "Helvetica"
            font.bold: true; font.pixelSize: 72
            style: Text.Raised; styleColor: "#757575"
        }

    }
}


/*##^##
Designer {
    D{i:8;anchors_height:42;anchors_width:1280}
}
##^##*/
