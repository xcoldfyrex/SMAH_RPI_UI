import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import smah.preset 1.0
import smah.light 1.0

Page {
    property var device: "_DEF"

    SMAHBackground {}
    id: page
    width: window.width
    height: 600
    visible: false
    SMAHHeader {
        id: header1
        x: 0
        y: 0
        width: 404
        height: 37
        Text {
            id: curr
            text:  device.getName
            color: "#fefdfd"
            font.pixelSize: 26
            //anchors{
                //top: parent.top
                //left: parent.left
            //}
        }
    }

    ListView {
        ScrollBar.vertical: ScrollBar {}
        id: presetListView
        anchors{
            left: parent.left
            bottom: parent.bottom
            right: parent.right
            top: header1.bottom

        }
        y: header1.height + 5
        boundsBehavior: Flickable.StopAtBounds
        Layout.fillWidth: true
        Layout.fillHeight: true
        highlightMoveDuration: 200
        highlightMoveVelocity: -1
        highlight: Rectangle {
            color: '#111111'
            width: 950
            Text {
                anchors.centerIn: parent
                //text: 'Hello ' + presetList.get(presetListView.currentIndex).name
                color: 'white'
            }
        }
        focus: true
        delegate: Component {
            Item {
                height: 35
                width: 950
                //width: presetListView.width
                Row {
                    width: parent.width
                    Text {
                        color: "#fefdfd"
                        text: presetList[index].name
                        font.pixelSize: 32
                        width: 300

                    }
                    Text {
                        color: "#636363"
                        text: presetList[index].hex
                        font.pixelSize: 32
                        //Layout.alignment: Qt.AlignCenter
                        width: 300
                    }

                    Image {
                        source: "image://images/" + index
                        Layout.alignment: Qt.AlignRight
                        //anchors.right: parent.right
                    }

                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        presetListView.currentIndex = index
                        device.setActivePreset(presetList[index])
                    }
                }
            }
        }


        Component.onCompleted: {
            presetListView.model = presetList
        }
    }
    SMAHButton {
        id: closeb
        text: "Close"
        onClicked: page.visible = false
        anchors{
            left: parent.left
        }
        y: 691
    }
}
