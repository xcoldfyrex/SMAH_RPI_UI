import QtQuick 2.0
import smah.weatherdata 1.0

import "."

Rectangle {
    id: screenSaver
    width: parent.width
    height: parent.height
    color: "black"
    Component.onCompleted: {
        window.showSaver()
    }
    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: {
            var ts = Qt.formatTime(new Date(),"hh:mm:ss")
            timeText.text = ts
        }
    }
    Text {
        id: timeText
        //fontSizeMode: Text.Fit
        elide: Text.ElideRight
        horizontalAlignment: Text.Center
        verticalAlignment: Text.Center
        color: Style.saverClockTextColor
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 400
        style: Text.Raised; styleColor: Style.saverClockTextDropColor
    }
    Text {
        id: temperature
        text: weatherdataitems[0].temp.toFixed(1) + "F\n" + weatherdataitems[0].rh + "%"
        elide: Text.ElideLeft
        horizontalAlignment: Text.Right
        //verticalAlignment: Text.Center
        anchors.bottom: parent.bottom
        color: Style.saverClockTextColor
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 72
        style: Text.Raised; styleColor: Style.saverClockTextDropColor
    }
}
