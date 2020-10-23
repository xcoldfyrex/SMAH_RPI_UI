import QtQuick 2.12
import QtQuick.Controls 2.5
import smah.light 1.0
import smah.zone 1.0
import smah.sensor 1.0

import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.3

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
    header: ToolBar {
        z: 2000
        id: toolBar
        //opacity: 0.9
        padding: 0
        topPadding: 0
        contentHeight: toolButton.implicitHeight
        Rectangle{
            //color: "#00000077"
            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: "#000024"
                }
                GradientStop {
                    position: 1
                    color: "#000000"
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
            anchors.rightMargin: 50
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
                        text: qsTr("Weather");
                        font.pixelSize: 32
                    }
                    width: parent.width
                    onClicked: {
                        //stackView.push("Page1Form.ui.qml")
                        drawer.close()
                    }
                }
                ItemDelegate {
                    SMAHLabel {
                        text: qsTr("System");
                        font.pixelSize: 32
                    }
                    width: parent.width
                    onClicked: {
                        stackView.push("System.qml")
                        drawer.close()
                        //stackView
                    }
                }
                Label {
                    text: ".\n"
                }

            }
        }
    }

    function changeZone(zoneName)
    {
        stackView.clear()
        stackView.push(ZoneCreation.zoneFunctions[zoneName])
        drawer.close()
    }

    StackView {
        id: stackView
        anchors.rightMargin: -222
        //initialItem: "MainForm.ui.qml"
        anchors.fill: parent

        Component.onCompleted: {
            for (var i=0; i<zoneList.length; i++) {
                ZoneCreation.zoneLightList[zoneList[i].getName] = zoneList[i].getLightList

                //console.log(zoneList[i].getLightList[1].getName)
                //ZoneCreation.createZoneOptions(zoneList[i], i)
                var component= Qt.createComponent("ZoneItem.qml")
                var loadwin = component.createObject(mainMenu, {id: i, zoneName: zoneList[i].getName, drawerID: "zoneDrawer" + i, lights: zoneList[i].getLightList })

                //for (var a=0; a<zoneList[i].getLightList.length; a++) {
                //console.log(zoneList[i].getLightList[a].getName)
                var zonecomponent= Qt.createComponent("ZoneOptions.qml")
                var zoneloadwin = zonecomponent.createObject(mainMenu, {zoneName: zoneList[i].getName, lights: zoneList[i].getLightList} )
                ZoneCreation.zoneFunctions[zoneList[i].getName] = zoneloadwin
            }
            //stackView.push(1)
        }
    }
    SMAHBackground {}

}


/*##^##
Designer {
    D{i:8;anchors_height:42;anchors_width:1280}
}
##^##*/
