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
    property var lights_
    property Zone zone_
    property var parentObject
    implicitWidth: parent.width
    implicitHeight: parent.height

GridLayout {
    Component.onCompleted:
    {
        if (lights_.length !== 0) {
            for (var i=0; i<lights_.length; i++) {
                if (lights_[i].getType === "PlusRGBWPM") {
                    var zonecomponent = Qt.createComponent("/Presets.qml")
                    var zoneloadwin = zonecomponent.createObject(parentObject, {device: lights_[i], zone: zone_, parentObject: lightControlPage})
                    zoneloadwin.visible = false
                    presetPages[lights_[i]] = zoneloadwin
                }
                if (lights_[i].getType === "PlusRGBWPM") {
                    var zonecomponentPicker = Qt.createComponent("/ColorPicker.qml")
                    var zoneloadwinPicker = zonecomponentPicker.createObject(parentObject, {device: lights_[i], zone:zone_, parentObject: lightControlPage})
                    zoneloadwinPicker.visible = false
                    pickerPages[lights_[i]] = zoneloadwinPicker
                }
            }
        }
    }
    ListView {
        id: lightList
        height: 8800
        model: lights_
        interactive: false
        delegate: RowLayout {
            height: 75
            spacing: 10
            Column {
                SMAHLabel {
                    text: lights[index].getName
                    font.pixelSize: 20
                    width: 200
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
        }
        snapMode: ListView.SnapToItem
        highlightRangeMode: ListView.StrictlyEnforceRange
    }
}
}
