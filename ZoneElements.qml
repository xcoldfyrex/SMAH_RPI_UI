import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import smah.light
import smah.zone

import "qrc:/SMAHComponents/"

Item {
    id: lightControlPage
    property var presetPages: ({})
    property var pickerPages: ({})
    property var timerPages: ({})
    property var scenePages: null
    property var lights
    property Zone zone
    property var parentObject
    implicitWidth: parent.width
    implicitHeight: parent.height


        Component.onCompleted:
        {
            if (lights.length !== 0) {
                for (var i=0; i<lights.length; i++) {
                    if (lights[i].getType === "PlusRGBWPM") {
                        var zonecomponent = Qt.createComponent("/Presets.qml")
                        var zoneloadwin = zonecomponent.createObject(parentObject, {device: lights[i], zone: zone, parentObject: lightControlPage})
                        zoneloadwin.visible = false
                        presetPages[lights[i]] = zoneloadwin
                    }
                    if (lights[i].getType === "PlusRGBWPM") {
                        var zonecomponentPicker = Qt.createComponent("/ColorPicker.qml")
                        var zoneloadwinPicker = zonecomponentPicker.createObject(parentObject, {device: lights[i], zone:zone, parentObject: lightControlPage})
                        zoneloadwinPicker.visible = false
                        pickerPages[lights[i]] = zoneloadwinPicker
                    }
                    var timercomponentPicker = Qt.createComponent("/ZoneComponents/Timers.qml")
                    var timerloadwinPicker = timercomponentPicker.createObject(parentObject, {device: lights[i], zone:zone, parentObject: lightControlPage})
                    timerloadwinPicker.visible = false
                    timerPages[lights[i]] = timerloadwinPicker
                }
            }
            var scenePicker = Qt.createComponent("/ZoneComponents/ZoneScenes.qml")
            var sceneloadwinPicker = scenePicker.createObject(parentObject, {zone:zone, parentObject: lightControlPage})
            sceneloadwinPicker.visible = false
            scenePages = sceneloadwinPicker
        }

        ListView {
            id: lightList
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
            implicitHeight: 600
            model: lights
            interactive: false
            //width: 1000
            delegate: RowLayout {
                height: 75
                spacing: 10
                anchors.right: parent.right
                anchors.left: parent.left
                Column {
                    SMAHLabel {
                        text: lights[index].getName
                        font.pixelSize: 20
                        width: 300
                    }
                }
                SMAHButton {
                    id: button
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusRGBWPM"){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Presets")
                    onClicked: {
                        var zoneloadwin = presetPages[lights[index]]
                        lightControlPage.visible = false
                        element.text = zone.getName + " > " + lights[index].getName
                        zoneloadwin.visible = true
                    }
                    visible: determine_vis()
                }
                SMAHButton {
                    id: pickerButton
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusRGBWPM"){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Color Picker")
                    onClicked: {
                        var zoneloadwin = pickerPages[lights[index]]
                        lightControlPage.visible = false
                        element.text = zone.getName + " > " + lights[index].getName
                        zoneloadwin.visible = true
                    }
                    visible: determine_vis()
                }

                SMAHButton {
                    id: offButton
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusRGBWPM"){
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
                Switch {
                    id: toggleButton
                    height: 100
                    width:100
                    indicator: Rectangle {
                        implicitWidth: 48
                        implicitHeight: 26
                        x: toggleButton.width - width - toggleButton.rightPadding
                        y: parent.height / 2 - height / 2
                        color: toggleButton.checked ? "black" : "black"
                        border.color: "black"

                        Rectangle {
                            x: toggleButton.checked ? parent.width - width : 0
                            width: 25
                            height: 25
                            color: "#777"
                            border.color: "black"
                        }
                    }
                    function determine_vis()
                    {
                        if (lights[index].getType === "Plus1PM" || lights[index].getType === "PlusWallDimmer" ){
                            return true
                        } else {
                            return false
                        }
                    }
                    onClicked: {
                        lights[index].setState(toggleButton.checked)
                    }
                    visible: determine_vis()
                    checked: lights[index].getState
                }

                Slider {
                    id: brightnessSlider
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusWallDimmer"){
                            return true
                        } else {
                            return false
                        }
                    }
                    from: 1
                    to: 100
                    stepSize: 1
                    implicitWidth: 150
                    implicitHeight: 50
                    visible: determine_vis()
                    value: lights[index].getBrightness
                    onMoved: {
                        lights[index].setBrightness(value)
                    }
                    handle: Rectangle {
                        id: handleId
                        x: brightnessSlider.visualPosition * (brightnessSlider.width - width)
                        y: (brightnessSlider.height - height) / 2
                        width: 15
                        height: brightnessSlider.height
                        color: "#12141C"
                    }
                    background: Rectangle {
                        y: (brightnessSlider.height - height) / 2
                        height: 20
                        color: "#ccc"

                        Rectangle {
                            width: brightnessSlider.visualPosition * parent.width
                            height: parent.height
                            color: "#777"
                        }
                    }
                }
                SMAHLabel {
                    text: lights[index].getBrightness + "%"
                    font.pixelSize: 20
                    width: handleId.width - 3
                    x: brightnessSlider.right + 10
                    y: handleId.y / 2
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusWallDimmer"){
                            return true
                        } else {
                            return false
                        }
                    }
                    visible: determine_vis()
                }

                /* just a spacer */
                Item {
                    Layout.fillWidth: true
                }

                SMAHButton {
                    id: timerButton
                    Layout.alignment: Qt.AlignRight
                    function determine_vis()
                    {
                        if (lights[index].getType === "PlusRGBWPM"){
                            return true
                        } else {
                            return false
                        }
                    }
                    text: qsTr("Timer")
                    onClicked: {
                        var zoneloadwin = timerPages[lights[index]]
                        lightControlPage.visible = false
                        element.text = zone.getName + " > " + lights[index].getName
                        zoneloadwin.visible = true
                    }
                    visible: true
                }


            }
            snapMode: ListView.SnapToItem
            highlightRangeMode: ListView.StrictlyEnforceRange
        }
        SMAHButton {
            id: sceneButton
            anchors {
                bottom: parent.bottom
            }
            visible: true
            text: qsTr("Scenes")
            onClicked: {
                lightControlPage.visible = false
                element.text = zone.getName + " > Scenes "
                scenePages.visible = true
            }
        }
}
