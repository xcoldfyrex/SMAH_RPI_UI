import QtQuick 2.0
import QtQuick.Controls 2.12
import smah.light 1.0
import smah.zone 1.0

Page {
    id: page
    title: "Overview"
    visible: false
    property string zoneName: "_DEF"
    property var lights: ({})
    Label {
        text: "Overview!"
    }
}
