import QtQuick 2.0

Rectangle {
    id: screenSaver
    width: parent.width
    height: parent.height
    color: "black"
    Component.onCompleted: {
        window.showSaver()
        for (var i=0; i<sensorList.length; i++)
        {
            if (sensorList[i].name === "Outside")
            {
                outsideIndex = i
            }
        }
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
        color: "#454545"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 400
        style: Text.Raised; styleColor: "#757575"
    }
    Text {
        id: temperature
        text: sensorList[outsideIndex].temperature.toFixed(1) + "F\n" + sensorList[outsideIndex].rh + "%"
        elide: Text.ElideLeft
        horizontalAlignment: Text.Right
        //verticalAlignment: Text.Center
        anchors.bottom: parent.bottom
        color: "#454545"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 72
        style: Text.Raised; styleColor: "#757575"
    }

}
