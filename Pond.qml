import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import smah.ponddata
import QtMultimedia
import QtCharts
import smah.dbmanager
import QtQuick.Controls.Material

import "."
import "SMAHComponents/"

Page {
    property real phHigh: 0
    property real phLow: 0
    property real tempHigh: 0
    property real tempLow: 0
    property real searchWindow: 1440
    id: pondpage
    visible: true
    x: 0
    SMAHBackground {}
    SMAHTBox {
        ColumnLayout {
            id: realTimeData
            Layout.fillWidth: true
            Layout.fillHeight: true
            SMAHHeader {
                id: header1
                y: 0
                width: 600
                Layout.alignment: Qt.AlignCenter
                Text {
                    id: element
                    color: "#ffffff"
                    text: qsTr("Pond Conditions")
                    font.pixelSize: Style.fontHeaderSize
                }
            }
            GridLayout {
                id: grid
                width: parent.width
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 0
                    Layout.column: 0
                    color: "#ffffff"
                    text: "PH: " + ponddataitems[0].ph.toFixed(1)
                    font.pixelSize: Style.fontCellSize
                }
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 0
                    Layout.column: 1
                    color: "#ffffff"
                    text: "Low: " + phLow.toFixed(1) + " High: " + phHigh.toFixed(1)
                    font.pixelSize: Style.fontCellSize
                }
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 0
                    Layout.column: 2
                    color: "#ffffff"
                    text: "Updated: " + (ponddataitems[0].updated >= 1000 ? Qt.formatDateTime(new Date(ponddataitems[0].updated * 1000), "MM/dd/yyyy hh:mm:ss") : "-")
                    font.pixelSize: Style.fontCellSize
                }

                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 1
                    Layout.column: 0
                    color: "#ffffff"
                    text: "Temperature: " + ponddataitems[0].temp.toFixed(1)
                    font.pixelSize: Style.fontCellSize
                }
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 1
                    Layout.column: 1
                    color: "#ffffff"
                    text: "Low: " + tempLow + " High: " + tempHigh
                    font.pixelSize: Style.fontCellSize
                }
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.row: 1
                    Layout.column: 2
                    color: "#ffffff"
                    text: "Updated: " + (ponddataitems[0].updated  >= 1000 ? Qt.formatDateTime(new Date(ponddataitems[0].updated * 1000), "MM/dd/yyyy hh:mm:ss") : "-")
                    font.pixelSize: Style.fontCellSize
                }
            }
            RowLayout {
                Layout.column: 2
                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.alignment: Layout::Al
                    Layout.row: 0
                    Layout.column: 3
                    color: "#ffffff"
                    text: "Window: "
                    font.pixelSize: Style.fontCellSize
                }
                ComboBox  {
                    id: control
                    font.pointSize: Style.fontCellSize
                    delegate: ItemDelegate {
                        width: control.width
                        contentItem: Text {
                            text: modelData
                            color: "white"
                            font.pointSize: Style.fontHeaderSize
                            elide: Text.ElideRight
                            verticalAlignment: Text.AlignVCenter
                        }
                        highlighted: control.highlightedIndex === index
                    }

                    contentItem: Text {
                        text: control.displayText
                        font: control.font
                        color: "white"
                        verticalAlignment: Text.AlignVCenter
                        elide: Text.ElideRight
                    }

                    background: Rectangle {
                        implicitWidth: 200
                        implicitHeight: 40
                        radius: 0
                        color: "black"
                    }

                    popup: Popup {
                        y: control.height - 1
                        width: control.width
                        implicitHeight: contentItem.implicitHeight
                        padding: 1
                        contentItem: ListView {
                            clip: true
                            implicitHeight: contentHeight
                            model: control.popup.visible ? control.delegateModel : null
                            currentIndex: control.highlightedIndex
                            ScrollIndicator.vertical: ScrollIndicator { }
                        }

                        background: Rectangle {
                            color: "black"
                        }
                    }

                    Layout.row: 0
                    Layout.column: 4
                    model: ["24H", "48H", "3D", "1W", "2W", "1M", "3M"]
                    onActivated: {
                        switch(currentText) {
                        case "24H":
                            searchWindow = 1440
                            break;
                        case "48H":
                            searchWindow = 1440 * 2
                            break;
                        case "3D":
                            searchWindow = 1440 * 3
                            break;
                        case "1W":
                            searchWindow = 10080
                            break;
                        case "2W":
                            searchWindow = 10080 * 2
                            break;
                        case "1M":
                            searchWindow = 43830
                            break;
                        case "3M":
                            searchWindow = 43830 * 3
                            break;

                        }
                        refreshTimer.restart()
                    }
                }
            }
        }
        ChartView {
            id: chartView
            title: "Water Conditions"
            titleColor: "#ffffff"
            anchors.top: realTimeData.bottom
            anchors.left: parent.left
            legend.alignment: Qt.AlignTop
            antialiasing: true
            height: 800
            width: parent.width
            backgroundColor: "transparent"
            legend.labelColor: "#ffffff"
            //![2]
            DateTimeAxis {
                id: barCategoriesAxis
                titleText: "Date"
                color: "#ffffff"
                labelsColor: color
                titleBrush: color
                format: "MM/dd \n hh:mm"
                tickCount: 12
            }

            ValueAxis{
                id: valueAxispH
                min: 6
                max: 9
                titleText: "pH"
                color: "#aaaaaa"
                labelsColor: color
                gridLineColor: color
                minorGridLineColor: color
                titleBrush: color
            }

            ValueAxis {
                id: valueAxisX
                // Hide the value axis; it is only used to map the line series to bar categories axis
                visible: false
                min: 0
                max: 5
            }

            ValueAxis{
                id: valueAxisY
                min: 30
                max: 0
                titleText: "Temperature [&deg;F]"
                color: "#ffffff"
                labelsColor: color
                gridLineColor: color
                minorGridLineColor: color
                titleBrush: color
            }
            LineSeries {
                id: tempSeries
                axisX: valueAxisX
                axisY: valueAxisY
                name: "Temperature"
                color: "#0099ff"
                width: 2
            }
            LineSeries {
                id: pHSeries
                axisX: valueAxisX
                axisY: valueAxispH
                name: "pH"
                color: "#ff00ff"
                width: 2
            }
            LineSeries {
                id: placeholder
                axisX: barCategoriesAxis
                axisY: valueAxisY
                width: 0
                visible: false
            }
        }

    }
    Timer {
        id: refreshTimer
        interval: 1000 * 30
        repeat: true
        triggeredOnStart: true
        running: true
        onTriggered: {
            var ts = Math.floor(Date.now() / 1000) - (searchWindow  * 60)
            var mod = searchWindow < 11000 ? "" : " AND ts % 360 = 0"
            var data = db.search('select temp,ph,ts from pond_readings WHERE ts >= ' + ts + mod + ' ORDER BY ts ASC LIMIT ' + searchWindow)
            //data.reverse();
            var min = 100
            var max = 1
            var tphmin = 100
            var tphmax = 1
            var datemin = 9999999999999
            var datemax = 0
            tempSeries.clear()
            pHSeries.clear()
            for (var i = 0; i < data.length; i++) {
                var vals = data[i].split(",")
                if (i % 30 == 0) {
                    if (vals[0] <= min) {
                        min = vals[0]
                    }
                    if (vals[0] >= max) {
                        max = vals[0]
                    }
                    if (vals[1] <= min) {
                        tphmin = vals[1]
                        phLow = tphmin
                    }
                    if (vals[1] >= max) {
                        tphmax = vals[1]
                        phHigh = tphmax
                    }
                    if (vals[2] <= datemin) {
                        datemin = vals[2]
                    }
                    if (vals[2] >= datemax) {
                        datemax = vals[2]
                    }
                    tempSeries.append(Number(i),vals[0])
                    if (Number(vals[1]) > 5 &&  Number(vals[1]) < 9) {
                        pHSeries.append(Number(i),Number(vals[1]).toFixed(1))
                    }
                    valueAxisX.min = 0;
                    valueAxisX.max = Number(i) + 1;
                }
            }
            valueAxisY.min = parseInt(min) - 3
            valueAxisY.max = parseInt(max) + 3
            tempLow = parseInt(min)
            tempHigh = parseInt(max)
            barCategoriesAxis.min = new Date(datemin * 1000)
            barCategoriesAxis.max = new Date(datemax * 1000)
        }
    }
}
