import QtQuick 2.0


Item {
    id : clock

    property var locale: Qt.locale()
    property string dateString


    function timeChanged() {
        currentDate = new Date()

        dateString = Date.fromLocaleString(locale, currentDate, "ddd yyyy-MM-dd hh:mm:ss")
    }

    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: timeText.text =  Qt.formatTime(new Date(),"hh:mm:ss")
    }

    Text {
        id: timeText
        fontSizeMode: Text.Fit
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignRight
        text: {
            updatesEnabled: timeText.time
            Qt.formatTime(new Date(), "hh:mm:ss") + "\n dfgdf"
        }
        color: "white"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 16
        style: Text.Raised; styleColor: "black"
        anchors.right: parent.right
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
