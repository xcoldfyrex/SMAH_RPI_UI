// menu item for each zone in main drawer

import QtQuick 2.12
import QtQuick.Controls 2.5

import "."

Rectangle {
    id: zoneMenu
    property string zoneName: "_DEF"
    property int index: 0
    property var lights
    property var id
    property var drawerID
    ItemDelegate {
        Component.onCompleted: background.color = Style.menubg
        id: zd
        objectName: "zd";
        parent: mainMenu
        height: 40
        Rectangle {
            color: Style.menubg
            width: parent.width
            height: parent.height
            ItemDelegate {
                //palette.active:  "#e21414"

                width: parent.width
                height: 40
                SMAHLabel {
                    text: qsTr(zoneName)
                    font.pixelSize: 40
                    //styleColor: "#e21414"
                    width: parent.width
                }
                onClicked: {
                    changeZone(index)
                }
                background: Rectangle {
                    color: {
                        if (highlighted)
                            return "red";
                        if (hovered)
                            return "green";
                        return "blue";
                    }
                }
                Component.onCompleted: {
                    background.color = Style.menubg
                    palette.window = Style.menubg
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
