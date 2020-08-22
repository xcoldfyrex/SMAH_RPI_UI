import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13

Page {
    id: page
    SMAHBackground {}

    GridLayout {
        id: grid
        columns: 2
        columnSpacing: 0
        anchors.margins: 5

        property var titles: [ "BUILD NUMBER", "BUILD DATE", "IP", "MAC", "Z-WAVE DRIVER" ]
        property var values: [ "value1", "value2", "value3", "value4", "value5" ]
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.top
        anchors.bottomMargin: -125
        anchors.right: parent.left
        anchors.left: parent.left
        rows: 0
        anchors.rightMargin: -216

        Repeater {
            model: grid.titles
            Label {
                Layout.row: index
                Layout.column: 0
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
            }
        }

        Repeater {
            model: grid.values
            Label {
                Layout.row: index
                Layout.column: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: modelData
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
