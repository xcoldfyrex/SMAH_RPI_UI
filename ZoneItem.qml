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

            Text {
                color: "#aeaeae"
                text: qsTr(zoneName)
                styleColor: "#e21414"
            }
        }
        width: mainMenu.width
        onClicked: {
            changeZone(zoneName)
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
