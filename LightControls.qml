import QtQuick 2.0
import QtQuick.Controls 2.5
import smah.light 1.0


Rectangle {
    property int light_type: 0
    property int light_id: 0
    property var lights: ({})

    Component.onCompleted: {
        console.log(lights[0].getName)

    }
    Row {
        id: row
        x: 8
        y: 8
        width: 468
        height: 376
    }

}
