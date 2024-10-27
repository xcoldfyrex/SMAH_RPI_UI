// menu item for each zone in main drawer

import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    id: zoneMenu
    property string zoneName: "_DEF"
    property int index: 0
    property var lights
    property var id
    property var drawerID
    ItemDelegate {
        id: zd
        objectName: "zd";
        parent: mainMenu
        height: 40
        Rectangle {
            color: "#08111d"
            width: parent.width
            height: parent.height
            ItemDelegate {
                width: parent.width
                height: 40
                SMAHLabel {
                    text: qsTr(zoneName)
                    font.pixelSize: 40
                    styleColor: "#e21414"
                    width: parent.width
                }
                onClicked: {
                    changeZone(index)
                }
            }
        }
        width: mainMenu.width

    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
