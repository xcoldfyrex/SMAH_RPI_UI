import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13

Page {
    GridLayout {
        id: gridLayout
        width: 100
        height: 100


        Text {
            id: element
            text: qsTr("Text")
            font.pixelSize: 12
        }
        Text {
            id: element1
            text: qsTr("Text")
            font.pixelSize: 12
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
