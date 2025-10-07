import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import smah.preset 1.0
import smah.light 1.0

Item {
    property var device: "_DEF"

    id: presetPage
    width: parent.width
    height: parent.height
    //width: 800
    //height: 800
    visible: false
    SMAHTBox {
        id: tbox
        SMAHHeader {
            id: header1
            y: 0
            width: 600
            Layout.alignment: Qt.AlignCenter
            Text {
                id: element
                color: "#ffffff"
                text: qsTr(device.getName)
                font.pixelSize: Style.fontHeaderSize
            }
        }

        ListView {
            ScrollBar.vertical: ScrollBar {}
            id: presetListView
            anchors{
                left: parent.left
                //bottom: closeb.bottom
                right: parent.right
                //top: header1.bottom

            }
            y: header1.height + 5
            height: 800 // tbox.height - header1.height
            boundsBehavior: Flickable.StopAtBounds
            Layout.fillWidth: true
            Layout.fillHeight: false
            highlightMoveDuration: 200
            highlightMoveVelocity: -1
            highlight: Rectangle {
                color: '#111111'
                width: header1.width
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
                    width: header1.width
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
            onClicked: {
                presetPage.visible = false
                box.visible = true
            }
            anchors{
                left: parent.left
                bottom: parent.bottom
            }
            anchors.leftMargin: 100
        }
    }
}
