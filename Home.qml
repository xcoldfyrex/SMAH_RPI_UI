import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Dialogs
//import QtQuick.Controls.Styles

Page {
    id: page
    width: 1000
    height: 800
    title: "Home"
    SMAHBackground {}
    Rectangle {
        id: frame
        color: "#08111d"
        opacity: 0.9
        border.color: "#00000000"
        width: 300
        height: parent.height
        Column {
            parent: frame
            anchors.fill: parent
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Perimeter")
                    font.pixelSize: 40
                }
                width: parent.width
                height: 40
                onClicked: {
                    stackOptions.setCurrentIndex(0)
                }
            }
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Environment")
                    font.pixelSize: 40
                }
                width: parent.width
                height: 40
                onClicked: {
                    stackOptions.setCurrentIndex(1)
                }
            }
            ItemDelegate {
                SMAHLabel {
                    text: qsTr("Climate Control")
                    font.pixelSize: 40
                }
                width: parent.width
                height: 40
                onClicked: {
                    //stackView.push("Page1Form.ui.qml")
                }
            }
        }
    }
    SwipeView
    {
        Perimeter {}
        Environment {}

        //parent: zoneOptions
        id: stackOptions
        interactive: false
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: frame.right
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
    }
}

/*##^##
Designer {
    D{i:5;anchors_y:34}D{i:7;anchors_y:34}
}
##^##*/
