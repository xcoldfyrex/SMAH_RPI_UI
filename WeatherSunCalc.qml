import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml.Models 2.2

import "suncalc.js" as SC

Page {
    id: weatherSunCalc
    title: "Sunrise"

    ListModel {
        id: sunTimes
    }

    function updateModel() {
        var now = new Date()
        sunTimes.clear()
        Number.prototype.pad = function(size) {
            var s = String(this);
            while (s.length < (size || 2)) {s = "0" + s;}
            return s;
        }
        for (var i=0; i< 40; i++) {
            var offset = 86400000 * i
            var prevday = new Date(now.getTime() + offset - 86400000)
            var day = new Date(now.getTime() + offset)
            var dayts = day.getTime()
            var times = SC.SunCalc.getTimes(day, 47.53, -122.56);
            var prevtimes = SC.SunCalc.getTimes(prevday, 47.53, -122.56);
            var sunrisePos = SC.SunCalc.getPosition(times.solarNoon, 47.530690, -122.607160);
            var dlyesterday = prevtimes.sunset.getTime() - prevtimes.sunrise.getTime();
            var dltoday = times.sunset.getTime() - times.sunrise.getTime();
            var dlh = Math.floor((dltoday / (1000*60*60)) % 24);
            var dlm = Math.ceil((dltoday / (1000*60)) % 60).pad();
            var diff = Math.abs(Math.floor((dltoday - dlyesterday) / 1000));
            var diffmin = Math.floor(diff / 60);
            var diffsec = diff - diffmin * 60;
            var diffstr = diffmin + "m:" + diffsec + "s";
            sunTimes.append({
                                "sr": times.sunrise.getHours().pad() + ':' + times.sunrise.getMinutes().pad(),
                                "ss": times.sunset.getHours().pad() + ':' + times.sunset.getMinutes().pad(),
                                "sn": times.solarNoon.getHours().pad() + ':' + times.solarNoon.getMinutes().pad(),
                                "dl": dlh + ":" + dlm,
                                "dd": diffstr,
                                "ts": (day.getMonth() + 1)  + '/' + day.getDate(),
                                "sa": (sunrisePos.altitude * 180 / Math.PI).toFixed(1)
                            });
        }
    }

    Timer { //single shot
        interval: 100; running: true; repeat: false;
        onTriggered: {
            updateModel()
        }
    }

    Timer {
        interval: 10000 * 6 * 60 * 12; running: true; repeat: true;
        onTriggered: {
            updateModel()
        }
    }

    SMAHBackground {}
    GridLayout {
        id: grid
        columnSpacing: 0
        anchors.margins: 5
        property var titles: [ "Date",  "Sunrise", "Sunset", "Length", "Diff", "Solar Noon" ]
        anchors.fill: parent
        Repeater {
            model: grid.titles
            SMAHLabel {
                Layout.row: 1
                Layout.column: index
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: modelData
                color: "#9c806e"
                font.pixelSize: 20
            }
        }

        //day
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 0
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: ts
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }

        //sunrise
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 1
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sr
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }

        //sunset
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 2
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: ss
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }

        //day length
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 3
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: dl
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }

        //day length diff
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 4
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: dd
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }
        Repeater {
            model: sunTimes
            SMAHLabel {
                Layout.column: 5
                Layout.columnSpan: 1
                Layout.row: index + 4
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: sn + " (" + sa +"°)"
                leftPadding: 5
                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft
                font.pixelSize: 14
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:4}
}
##^##*/
