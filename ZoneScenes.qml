import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import smah.zone
import smah.light
import smah.scene

import "qrc:/SMAHComponents/"

Item {
    id: sceneControlPage
    property Zone zone
    property var parentObject
    implicitWidth: parent.width
    implicitHeight: parent.height
    ListView {
        ScrollBar.vertical: ScrollBar {}
        id: sceneListView
        anchors{
            left: parent.left
            right: parent.right
        }
        height: parent.height
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
        focus: true
        delegate: Component {
            Item {
                height: 35
                width: 300
                Row {
                    width: parent.width
                    Text {
                        color: "#fefdfd"
                        text: zone.getSceneList[index].name
                        font.pixelSize: 32
                        width: 300
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        sceneListView.currentIndex = index
                        zone.getSceneList[index].activate()
                    }
                }
            }
        }
        Component.onCompleted: {
            sceneListView.model = zone.getSceneList
        }
    }

    SMAHButton {
        id: closeb
        text: "Close"
        onClicked: {
            sceneControlPage.visible = false
            element.text = zone.getName
            parentObject.visible = true
        }
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
    }
}
