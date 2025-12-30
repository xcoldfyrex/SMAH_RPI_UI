import QtQuick 2.0
import smah.weatherdata 1.0
import smah.ponddata

import "."

Rectangle {
    id: screenSaver
    width: parent.width
    height: parent.height
    color: "black"
    z: 99999
    Component.onCompleted: {
        window.showSaver()
    }
    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: {
            var ts = Qt.formatTime(new Date(),"hh:mm:ss")
            timeText.text = ts
            determinePondReadout()
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
    Text {
        id: pond
        text: determinePondReadout()
        elide: Text.ElideLeft
        horizontalAlignment: Text.Right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Style.saverClockTextColor
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 60
        style: Text.Raised; styleColor: Style.saverClockTextDropColor
    }

    function determinePondReadout()
    {
        var now = Math.floor(Date.now() / 1000)
        var text = ponddataitems[0].temp.toFixed(1) + "F\n" + "pH " + ponddataitems[0].ph.toFixed(1)
        if (now - ponddataitems[0].updated > 60)
        {
            text = "⚠"
        }
        pond.text = text
    }
}
