import QtQuick 2.0


Item {
    id : clock

    property int hours
    property int minutes
    property int seconds
    property real shift
    property bool night: false
    property bool internationalTime: false //Unset for local time

    function timeChanged() {
        var date = new Date;
        hours = internationalTime ? date.getUTCHours() + Math.floor(clock.shift) : date.getHours()
        night = ( hours < 7 || hours > 19 )
        minutes = internationalTime ? date.getUTCMinutes() + ((clock.shift % 1) * 60) : date.getMinutes()
        seconds = date.getUTCSeconds();
    }

    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: clock.timeChanged()
    }

    Text {
        fontSizeMode: Text.Fit
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignRight
        text: hours + ":" + minutes + ":" + seconds
        color: "white"
        font.family: "Helvetica"
        font.bold: true; font.pixelSize: 16
        style: Text.Raised; styleColor: "black"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
