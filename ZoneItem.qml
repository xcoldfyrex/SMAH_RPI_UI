// menu item for each zone in main drawer

import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    id: zoneMenu
    property string zoneName: "_DEF"
    ItemDelegate {
        id: zd
        objectName: "zd";
        parent: mainMenu
        Rectangle {
            color: "#08111d"
            width: parent.width
            height: parent.height
            ItemDelegate {
                width: parent.width
                SMAHLabel {
                    text: qsTr(zoneName)
                    font.pixelSize: 32
                    styleColor: "#e21414"
                    width: parent.width
                }
                onClicked: {
                    changeZone(zoneName)
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
