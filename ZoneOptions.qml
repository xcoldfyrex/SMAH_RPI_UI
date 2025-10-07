import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light
import smah.zone

// shows a list of lights associated with the device
Page {
    // create a single map of the objects ahead of time
    property var presetPages: ({})
    property var pickerPages: ({})
    property var lights
    property var zoneName


    SMAHBackground {}
    id: page
    title: zoneName
    Component.onCompleted:
    {
        if (lights.length !== 0) {
            for (var i=0; i<lights.length; i++) {
                if (lights[i].getType >= 10) {
                    var zonecomponent = Qt.createComponent("Presets.qml")
                    var zoneloadwin = zonecomponent.createObject(page, {device: lights[i]})
                    presetPages[lights[i]] = zoneloadwin
                }
                if (lights[i].getType >= 10) {
                    var zonecomponentPicker = Qt.createComponent("ColorPicker.qml")
                    var zoneloadwinPicker = zonecomponentPicker.createObject(page, {device: lights[i]})
                    pickerPages[lights[i]] = zoneloadwinPicker
                }
            }
        }
    }
    SMAHTBox {
        id: box
        SMAHHeader {
            id: header1
            y: 0
            width: 600
            Layout.alignment: Qt.AlignCenter
            Text {
                id: element
                color: "#ffffff"
                text: qsTr(zoneName)
                font.pixelSize: Style.fontHeaderSize
            }
        }
        ListView {
            id: lightList
            anchors{
                top: header1.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            height: 200
            model: lights
            interactive: false
            delegate: RowLayout {
                height: 75
                //anchors.fill: parent
                spacing: 10
                Column {
                    SMAHLabel {
                        //Layout.alignment: Qt.AlignVCenter
                        text: lights[index].getName
                        font.pixelSize: 20
                        width: 200
                    }
                }
                SMAHButton {
                    id: button
                    function determine_vis()
                    {
                        if (lights[index].getType >= 10){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Presets")
                    onClicked: {
                        var zoneloadwin = presetPages[lights[index]]
                        box.visible = false
                        zoneloadwin.visible = true
                    }
                    visible: determine_vis()
                }
                SMAHButton {
                    id: pickerButton
                    function determine_vis()
                    {
                        if (lights[index].getType >= 10){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Color Picker")
                    onClicked: {
                        var zoneloadwin = pickerPages[lights[index]]
                        box.visible = false
                        zoneloadwin.visible = true
                    }
                    visible: determine_vis()
                }

                SMAHButton {
                    id: offButton
                    function determine_vis()
                    {
                        if (lights[index].getType >= 10){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Off")
                    onClicked: {
                        lights[index].setColor("00000000")
                    }
                    visible: determine_vis()
                }
            }
            snapMode: ListView.SnapToItem
            highlightRangeMode: ListView.StrictlyEnforceRange
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
