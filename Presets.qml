import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import smah.preset
import smah.zone
import smah.objectfactory

import "qrc:/SMAHComponents/"

Item {
    property var device: "_DEF"
    property var parentObject
    property Zone zone
    id: presetPage
    width: parent.width
    height: parent.height

    ListView {
        ScrollBar.vertical: SMAHScrollBar { }
        id: presetListView
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: closeb.top
        }
        implicitHeight: 500 //parent.height
        boundsBehavior: Flickable.StopAtBounds
        Layout.fillWidth: true
        Layout.fillHeight: true
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
                        text: factory.getPresetObjects()[index].name
                        font.pixelSize: 32
                        width: 300

                    }
                    Text {
                        color: "#636363"
                        text: factory.getPresetObjects()[index].hex
                        font.pixelSize: 32
                        width: 300
                    }

                    Image {
                        source: "image://images/" + index
                        Layout.alignment: Qt.AlignRight
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        presetListView.currentIndex = index
                        device.setActivePreset(factory.getPresetObjects()[index])
                    }
                }
            }
        }

        Component.onCompleted: {
            presetListView.model = factory.getPresetObjects()
        }
    }

    SMAHButton {
        id: closeb
        text: "Close"
        onClicked: {
            presetPage.visible = false
            element.text = zone.getName
            parentObject.visible = true
        }
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
    }
}
