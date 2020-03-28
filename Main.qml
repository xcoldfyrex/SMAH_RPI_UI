import QtQuick 2.12
import QtQuick.Controls 2.5
import smah.light 1.0
import smah.zone 1.0
import QtQuick.Controls.Material 2.12

import "zoneCreation.js" as ZoneCreation

MainForm {    
    SMAHBackground {}

    //signal zoneChanged(string zoneName)

    id: window
    visible: true
    width: 1280
    height: 800
    title: qsTr("Stack")
    objectName: "toolBar";
    Component.onCompleted: {
        //console.log(lightList.size)

        for (var i=0; i<zoneList.length; i++) {
            //console.log(zoneList[i].getLightList[1].getName)
            //ZoneCreation.createZoneOptions(zoneList[i], i)
            var component= Qt.createComponent("ZoneItem.qml")
            var loadwin = component.createObject(mainMenu, {id: i, zoneName: zoneList[i].getName, drawerID: "zoneDrawer" + i, lights: zoneList[i].getLightList })
            //stackView.push(loadwin)
        }
    }


    header: ToolBar {
        id: toolBar
        opacity: 0.9
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
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
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

        Column {
            anchors.fill: parent
            objectName: "mainMenu";
            id: mainMenu
            ItemDelegate {
                text: qsTr("Weather")
                width: parent.width
                onClicked: {
                    //stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("System")
                width: parent.width
                onClicked: {
                    //stackView.push("Page2Form.ui.qml")
                    drawer.close()
                    stackView
                }
            }
            Label {
                text: ".\n"
            }

        }
    }

    function changeZone(zoneName)
    {
        console.log(zoneName)
        var component= Qt.createComponent("ZoneOptions.qml")
        var loadwin = component.createObject(mainMenu)
        stackView.push(loadwin)
    }

    StackView {
        id: stackView
        anchors.rightMargin: -222
        //initialItem: "MainForm.ui.qml"
        anchors.fill: parent
    }
}


/*##^##
Designer {
    D{i:9;anchors_height:42;anchors_width:1280}
}
##^##*/
