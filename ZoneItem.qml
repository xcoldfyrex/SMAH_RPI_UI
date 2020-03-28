import QtQuick 2.12
import QtQuick.Controls 2.5

Rectangle {
    //property int id: 0
    property string zoneName: "_DEF"
    property string drawerID: "_DEF"
    ItemDelegate {
        id: zd
        objectName: "zd";
        parent: mainMenu
        text: qsTr(zoneName)
        width: mainMenu.width
        onClicked: {
            changeZone(zoneName)
            //window.zone
        }
    }


}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
