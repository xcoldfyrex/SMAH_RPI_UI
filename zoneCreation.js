var zoneitem

function createZoneOptions(index, id) {
    var zoneitem = Qt.createQmlObject(`import QtQuick 2.12
import QtQuick.Controls 2.5
ItemDelegate {
    text: qsTr("${index}")
    width: parent.width
    onClicked: {
        zoneDrawer${id}.open
    }

    Drawer {
        id: zoneDrawer${id}
        parent: window
        width: window.width * 0.33
        Column {
            transform: Translate {
                x: 500
            }
            anchors.fill: drawer.Right
            objectName: "zoneLight{$id}";
            id: zoneLight${id}
            ItemDelegate {
                text: qsTr("Lights")
                width: parent.width
                onClicked: {
                    //stackView.push("Page1Form.ui.qml")
                    drawer.close()
                }
            }
        }
    }
}`, mainMenu, "zone"+index);
console.log(zoneitem)
}


