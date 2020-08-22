import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light 1.0
import smah.zone 1.0
import "LightOverviewElement.js" as LE

// shows a list of lights associated with the device

Page {
    SMAHBackground {}
    id: page
    property string zoneName: "_DEF"
    property var lights: ({})
    property var lightNames: ([])
    title: "Device control"

    visible: false

    // Label {
    // for tomorrow - build a list of shit
    //      text: "dsfds"

    //}


    GridLayout {
        id: gridParent
        property var titles:  [ "fsss","hddd", "teee" ]

        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.top
        anchors.bottomMargin: -125
        anchors.right: parent.left
        anchors.left: parent.left
        parent: page
        rows: 0
        columns: 2
        Component.onCompleted: {

            if (lights.length > 0) {
                LE.createLightList(lights, gridParent, 0)
                //for (var i=0; i<=lights.length-1; i++) {
                //                    LE.createWhiteLight(lights[i], gridParent, i)
                //}
            }
        }

    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
