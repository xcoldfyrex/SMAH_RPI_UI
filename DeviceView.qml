import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light 1.0
import smah.zone 1.0

// shows a list of lights associated with the device
Page {
    // create a single map of the objects ahead of time
    property var presetPages: ({})
    property var pickerPages: ({})


    SMAHBackground {}
    id: page
    title: "Device control"
    width: 300
    height: 600
    Component.onCompleted:
    {
        if (lights.length !== 0) {
            for (var i=0; i<lights.length; i++) {
                var zonecomponent = Qt.createComponent("Presets.qml")
                var zoneloadwin = zonecomponent.createObject(page, {device: lights[i]})
                presetPages[lights[i]] = zoneloadwin
                var zonecomponentPicker = Qt.createComponent("ColorPicker.qml")
                var zoneloadwinPicker = zonecomponentPicker.createObject(page, {device: lights[i]})
                pickerPages[lights[i]] = zoneloadwinPicker
            }
        }
    }
    ListView {
        id: lightList
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: 200
        model: lights
        interactive: false
        delegate: Row {
            //anchors.fill: parent

            spacing: 10
            Text {
                color: "#fefdfd"
                text: lights[index].getName
                font.pixelSize: 20
                width: 200
            }

            Slider {
                function determine_vis()
                {
                    //console.log(lights[index].getType)
                    if (lights[index].getType === 1){
                        return true
                    } else {
                        return false
                    }
                }
                visible: determine_vis
                id: level
                x: 179
                y: 10
                width: 302
                height: 22
                value: 0.0
                onMoved: {
                    lights[index].setLevel(level.value * 100)
                }
            }

            Text {
                id: txtValue
                x: 517
                width: 45
                height: 15
                color: "#ffffff"
                text: lights[index].getLevel
                font.pixelSize: 20
            }
            Switch {
                function determine_vis()
                {
                    //console.log(lights[index].getType)
                    if (lights[index].getType === 0){
                        return true
                    } else {
                        return false
                    }
                }
                visible: determine_vis()
                checked: false
                text: qsTr("Off")
                onClicked: {
                    //lights[index].toggleState()
                }
            }

            Button {
                id: button
                x: 694
                y: 10
                text: qsTr("Presets")
                onClicked: {
                    var zoneloadwin = presetPages[lights[index]]
                    zoneloadwin.visible = true
                }

                //right: parent.width - button.width
            }
        }
        snapMode: ListView.SnapToItem
        highlightRangeMode: ListView.StrictlyEnforceRange
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/