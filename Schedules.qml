import QtQuick
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.13
import QtQuick.Controls.Material

import smah.objectfactory

import "."
import "qrc:/SMAHComponents"
import "virtuallight.js" as Light

Page {
    id: actionpage
    visible: true
    x: 0

    property var light: new Light.Light()
    property var shellyObjects: factory.getShellyObjects()

    SMAHBackground {}
    Keyboard {
        visible: false
        id: keyboardOverlay
        x: 0
        y: 0
    }

    SMAHTBox {
        ColumnLayout {
            id: topBar
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
                    text: qsTr("Scheduled Actions")
                    font.pixelSize: Style.fontHeaderSize
                }
            }
        }
        ColorPicker {
            id: picker
            anchors.top: topBar.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            visible: false
            zone: null
            device: light
            parentObject: mainGrid
        }
        GridLayout {
            id: mainGrid
            anchors.top: topBar.bottom
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            ListView {
                ScrollBar.vertical: SMAHScrollBar { }
                id: scheduleListView
                width: 400
                implicitWidth: 400
                height: 200
                boundsBehavior: Flickable.StopAtBounds
                Layout.fillHeight: true
                Layout.column: 0
                Layout.row: 0
                Layout.rowSpan: 50
                Layout.columnSpan: 2
                highlightMoveDuration: 200
                highlightMoveVelocity: -1
                clip: true
                highlight: Rectangle {
                    color: '#666666'
                    width: scheduleListView.width
                    Text {
                        anchors.centerIn: parent
                        color: 'white'
                    }
                }
                focus: true
                delegate: Component {
                    Item {
                        height: 35
                        width: scheduleListView.width
                        Row {
                            width: parent.width
                            Text {
                                color: "#fefdfd"
                                text: factory.getActionObjects()[index].name
                                font.pixelSize: 32
                                width: scheduleListView.width
                            }
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                scheduleListView.currentIndex = index
                                scheduleItemsListView.model = configuration.getActionItemConfigurations(index)
                                scheduleItemsListView.currentIndex = 0
                            }
                        }
                    }
                }

                Component.onCompleted: {
                    scheduleListView.model = factory.getActionObjects()
                }
            }
            SMAHButton {
                text: "+"
                Layout.column: 0
                Layout.row: 50
                onClicked: {
                    keyboardOverlay.visible = true
                    //configuration.addActionSetConfigurations(scheduleListView.currentIndex)
                    //scheduleListView.model = factory.getActionObjects()
                }
            }

            SMAHButton {
                text: "-"
                Layout.column: 1
                Layout.row: 50
                onClicked: {
                    if (scheduleListView.model.length !== 0 ) {
                        configuration.delActionSetConfigurations(scheduleListView.currentIndex)
                        scheduleListView.model = factory.getActionObjects()
                        scheduleItemsListView.currentIndex = 0
                    }
                }
            }

            ListView {
                ScrollBar.vertical: SMAHScrollBar { }
                id: scheduleItemsListView
                width: 10000
                implicitWidth: 1000
                height: 400
                boundsBehavior: Flickable.StopAtBounds
                Layout.column: 2
                Layout.row: 0
                highlightMoveDuration: 200
                highlightMoveVelocity: -1
                clip: true
                highlight: Rectangle {
                    color: '#666666'
                    width: scheduleItemsListView.width
                    Text {
                        anchors.centerIn: parent
                        color: 'white'
                    }
                }
                focus: true

                delegate: Component {
                    Item {
                        height: 35
                        width: scheduleItemsListView.width - 30
                        RowLayout {
                            width: parent.width
                            SMAHLabel {
                                text: "Action=" + modelData.mAction
                                font.pixelSize: Style.fontSmallSize
                            }
                            SMAHLabel {
                                text: "Value=" + modelData.mValue
                                font.pixelSize: Style.fontSmallSize
                            }
                            SMAHLabel {
                                text: "Time/Time Offset=" + modelData.mTime
                                font.pixelSize: Style.fontSmallSize
                            }
                            SMAHLabel {
                                text: "Repeat Count=" + modelData.mRepeat
                                font.pixelSize: Style.fontSmallSize
                            }
                            SMAHLabel {
                                text: "Repeat Interval=" + modelData.mInterval
                                font.pixelSize: Style.fontSmallSize
                            }
                        }

                        MouseArea {
                            id: editItemArea
                            //Component.onCompleted: editItemArea.
                            anchors.fill: parent
                            onClicked: {
                                scheduleItemsListView.currentIndex = index
                                actionBox.currentValue = modelData.mAction
                                repeatBox.value = modelData.mRepeat
                                if (modelData.mTime.startsWith("+"))
                                {
                                    timeOffsetValue.currentValue = modelData.mTime
                                    timeFixedRow.visible = false
                                    timeOffsetRow.visible = true
                                } else {
                                    timeFixedHour.currentValue = modelData.mTime.split(":")[0]
                                    timeFixedMinute.currentValue = modelData.mTime.split(":")[1]
                                    timeFixedRow.visible = true
                                    timeOffsetRow.visible = false
                                }

                                if (modelData.mAction === "SHELLY_RGB") {
                                    lblValueFixed.text = modelData.mValue
                                }

                                if (modelData.mAction === "SHELLY_OFFSET" || modelData.mAction === "SHELLY_OFFSET_WHITE" || modelData.mAction === "SHELLY_BRIGHTNESS") {
                                    spnValueOffset.value = modelData.mValue
                                }
                            }
                        }
                    }
                }
            }
            ColumnLayout {
                id: controls
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignTop
                Layout.column: 3
                Layout.row: 0
                height: 500

                RowLayout {
                    SMAHButton {
                        id: editButton
                        text: "Edit"
                        onClicked: {
                            editControls.visible = true
                            doneButton.visible = true
                            editButton.visible = false
                            saveConfigButton.visible = false
                            scheduleListView.enabled = false
                            deviceCheckBoxes.visible = true
                        }
                    }
                    SMAHButton {
                        id: saveConfigButton
                        text: "Save Configuration"
                        onClicked: {
                            configuration.saveActionItemConfigurations()
                            updateDevices()
                            factory.createActionObjects(configuration);
                        }
                        function updateDevices() {
                            var checkedList = []
                            var i = 0
                            for ( i = 0; i < shellyObjects.length; i++) {
                                var delegateItem = deviceCheckBoxes.itemAtIndex(i)
                                if (delegateItem) {
                                    if (delegateItem.checked) {
                                        checkedList.push(delegateItem.text)
                                    }
                                }
                            }
                            configuration.updateActionConfigurations(scheduleListView.currentIndex, checkedList)
                        }
                    }
                    SMAHButton {
                        id: doneButton
                        text: "Done"
                        visible: false
                        onClicked: {
                            editControls.visible = false
                            doneButton.visible = false
                            editButton.visible = true
                            saveConfigButton.visible = true
                            scheduleListView.enabled = true
                            deviceCheckBoxes.visible = false
                        }
                    }
                }
                ButtonGroup {
                    id: childGroup
                    exclusive: false
                }
                ListView {
                    id: deviceCheckBoxes
                    visible: false
                    model: shellyObjects
                    implicitHeight: 300
                    width: 300
                    ScrollBar.vertical: SMAHScrollBar { }
                    clip: true
                    cacheBuffer: 10000
                    delegate: SMAHCheckBox {
                        id: modelCheckBoxes
                        checked: configuration.getActionConfigurationDevices(scheduleListView.currentIndex).includes(factory.getShellyObjects()[index].id)
                        text: factory.getShellyObjects()[index].id
                        indicator.width: 15
                        indicator.height: 15
                        ButtonGroup.group: childGroup
                    }
                }
            }
            GridLayout {
                id: editControls
                visible: false
                Layout.column: 1
                Layout.columnSpan: 5
                Layout.row: 1
                Layout.fillWidth: true
                SMAHLabel {
                    Layout.column: 0
                    Layout.row: 0
                    text: "Type"
                    font.pixelSize: Style.fontCellSize
                }
                SMAHComboBox  {
                    Layout.column: 1
                    Layout.row: 0
                    id: actionBox
                    popupHeight: controls.height + 300
                    width: 800
                    implicitWidth: width
                    model: [
                        "SHELLY_ON",
                        "SHELLY_BRIGHTNESS",
                        "SHELLY_RGB",
                        "SHELLY_WHITE",
                        "SHELLY_TRANSITION_DURATION",
                        "SHELLY_TOGGLE_AFTER",
                        "SHELLY_OFFSET",
                        "SHELLY_OFFSET_WHITE"
                    ]
                    onCurrentTextChanged: {
                        if (currentText === "SHELLY_OFFSET" || currentText === "SHELLY_OFFSET_WHITE" || currentText === "SHELLY_BRIGHTNESS") {
                            repeatLabel.visible = true
                            repeatBox.visible = true
                            btnOffset.checked = true
                            valueButtonRowAll.enabled = true
                            btnOffset.click()
                            valueButtonRowAll.enabled = false
                        } else if (currentText === "SHELLY_RGB") {
                            repeatLabel.visible = false
                            repeatBox.visible = false
                            btnColorVal.checked = true
                            valueButtonRowAll.enabled = true
                            btnColorVal.click()
                            valueButtonRowAll.enabled = false
                        } else {
                            repeatLabel.visible = false
                            repeatBox.visible = false
                            valueButtonRowAll.enabled = true
                        }
                    }
                }

                SMAHLabel {
                    id: repeatLabel
                    Layout.column: 0
                    Layout.row: 1
                    text: "# of Repeats"
                    font.pixelSize: Style.fontCellSize
                }
                SMAHSpinBox {
                    id: repeatBox
                    Layout.column: 1
                    Layout.row: 1
                    from: 0
                    to: 100
                    stepSize: 1
                }

                SMAHLabel {
                    Layout.column: 0
                    Layout.row: 2
                    text: "Time or offset"
                    font.pixelSize: Style.fontCellSize
                }
                /* time and offsets */
                RowLayout {
                    Layout.column: 1
                    Layout.row: 2
                    ButtonGroup {
                        id: timeButtonGroup
                    }
                    SMAHRadioButton {
                        checked: true
                        text: "Fixed Time"
                        ButtonGroup.group: timeButtonGroup
                        onClicked: {
                            timeFixedRow.visible = true
                            timeOffsetRow.visible = false
                        }
                    }
                    SMAHRadioButton {
                        text: "Time Offset"
                        ButtonGroup.group: timeButtonGroup
                        onClicked: {
                            timeFixedRow.visible = false
                            timeOffsetRow.visible = true
                        }
                    }
                    SMAHRadioButton {
                        text: "Dynamic Time"
                        ButtonGroup.group: timeButtonGroup
                        onClicked: {
                            timeFixedRow.visible = false
                        }
                    }
                }
                RowLayout {
                    Layout.column: 1
                    Layout.row: 3
                    Row {
                        id: timeFixedRow
                        SMAHLabel{
                            text: "Hour "
                            font.pixelSize: Style.fontSmallSize
                        }
                        SMAHComboBox {
                            id: timeFixedHour
                            width: 100
                            implicitWidth: width
                            model: Array.from(Array(24).keys(),(_, i) => String(i).padStart(2, '0'))
                            popupHeight: controls.height + 300
                        }
                        SMAHLabel{
                            text: "Minute "
                            font.pixelSize: Style.fontSmallSize
                        }
                        SMAHComboBox {
                            id: timeFixedMinute
                            width: 100
                            implicitWidth: width
                            model: Array.from(Array(60).keys(),(_, i) => String(i).padStart(2, '0'))
                            popupHeight: controls.height + 300
                        }
                    }
                    Row {
                        id: timeOffsetRow
                        visible: false
                        SMAHComboBox {
                            id: timeOffsetValue
                            model: Array.from(Array(60).keys())
                            popupHeight: controls.height + 300
                        }
                    }
                }
                /* value types */
                SMAHLabel {
                    Layout.column: 0
                    Layout.row: 4
                    text: "Value"
                    font.pixelSize: Style.fontCellSize
                }
                RowLayout {
                    Layout.column: 1
                    Layout.row: 4

                    Row {
                        id: valueButtonRowAll
                        ButtonGroup {
                            id: valueButtonGroupAll
                        }
                        SMAHRadioButton {
                            checked: true
                            id: btnColorVal
                            text: "Fixed Value"
                            ButtonGroup.group: valueButtonGroupAll
                            onClicked: {
                                valueFixedRow.visible = true
                                valueOffsetRow.visible = false
                            }
                        }
                        SMAHRadioButton {
                            id: btnOffset
                            text: "Value Offset/Level"
                            ButtonGroup.group: valueButtonGroupAll
                            onClicked: {
                                valueFixedRow.visible = false
                                valueOffsetRow.visible = true
                            }
                        }
                        SMAHRadioButton {
                            text: "Scene"
                            ButtonGroup.group: valueButtonGroupAll
                            onClicked: {
                                valueFixedRow.visible = false
                            }
                        }
                    }
                }
                RowLayout {
                    Layout.column: 1
                    Layout.row: 5
                    RowLayout {
                        id: valueFixedRow
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        SMAHButton {
                            id: openPicker
                            text: "Choose color"
                            onClicked: {
                                picker.visible = true
                                mainGrid.visible = false
                            }
                        }
                        SMAHLabel {
                            id: lblValueFixed
                            text: light.getColor()
                            font.pixelSize: Style.fontCellSize
                            Connections {
                                target: picker
                                function onUpdateRGB() {
                                    lblValueFixed.text = light.getColor()
                                }
                            }
                        }
                    }
                    RowLayout {
                        id: valueOffsetRow
                        visible: false
                        SMAHSpinBox {
                            Layout.column: 1
                            Layout.row: 1
                            id: spnValueOffset
                            from: -100
                            to: 100
                            value: 0
                            stepSize: 1
                        }
                    }
                }
                Item {
                    Layout.row: 9
                    Layout.fillHeight: true
                }

                SMAHButton {
                    id: saveButton
                    Layout.column: 0
                    Layout.row: 10
                    text: "Save Item"
                    onClicked: {
                        var tempTime = "00:00"
                        var tempValue = 0

                        switch (timeButtonGroup.checkedButton.text) {
                        case "Fixed Time":
                            tempTime = timeFixedHour.currentText + ":" + timeFixedMinute.currentText
                            break
                        case "Time Offset":
                            tempTime = timeOffsetValue.currentText
                            break
                        case "Dynamic Time":
                            break
                        }

                        switch (valueButtonGroupAll.checkedButton.text) {
                        case "Fixed Value":
                            tempValue = light.getColor()
                            break

                        case "Value Offset/Level":
                            tempValue = spnValueOffset.value
                            break
                        case "Scene":

                        }

                        configuration.updateActionItemConfigurations(scheduleListView.currentIndex,
                                                                     scheduleItemsListView.currentIndex,
                                                                     actionBox.currentText,
                                                                     tempValue,
                                                                     tempTime,
                                                                     repeatBox.value,
                                                                     1)
                        doneButton.clicked()
                        scheduleItemsListView.model = configuration.getActionItemConfigurations(scheduleListView.currentIndex)
                    }
                }
                SMAHButton {
                    id: deleteButton
                    Layout.column: 1
                    Layout.row: 10
                    text: "Delete Item"
                    onClicked: {
                        if (scheduleItemsListView.model.length !== 0 ) {
                            configuration.delActionItemConfigurations(scheduleListView.currentIndex, scheduleItemsListView.currentIndex)
                            scheduleItemsListView.model = configuration.getActionItemConfigurations(scheduleListView.currentIndex)
                            scheduleItemsListView.currentIndex = 0
                        }
                    }
                }
                SMAHButton {
                    id: newButton
                    Layout.column: 2
                    Layout.row: 10
                    text: "New Item"
                    onClicked: {
                        configuration.addActionItemConfigurations(scheduleListView.currentIndex)
                        scheduleItemsListView.model = configuration.getActionItemConfigurations(scheduleListView.currentIndex)
                    }
                }
            }
        }
    }
}
