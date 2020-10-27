import QtQuick 2.0


Item {
    id : clock
    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: {
            var ts = Qt.formatTime(new Date(),"hh:mm:ss")
            var ds = Qt.formatDate(new Date(),"MM/dd/yyyy")
            timeText.text = ts  + "\n" + ds
        }
    }
    Text {
        id: timeText
        fontSizeMode: Text.Fit
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignRight
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
