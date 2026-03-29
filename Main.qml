import QtQuick 2.12
import QtQuick.Controls 2.5
//import QtGraphicalEffects
import Qt5Compat.GraphicalEffects
import smah.light 1.0
import smah.sensor 1.0
import "."
import QtQuick.Window 2.3
import QtMultimedia 5.12

import "qrc:/SMAHComponents/"

ApplicationWindow {
    id: window
    visible: true
    width: 1920
    height: 1080
    minimumWidth: 1920
    maximumWidth: 1920
    minimumHeight: 1080
    maximumHeight: 1080
    title: qsTr("SMAH")
    objectName: "toolBar";
    color: "black"

    property int outsideIndex: 0

    signal saverActive()

    background: SMAHBackground {
        // Background stretches to fill entire window
        anchors.fill: parent
    }

    Connections {
        target: idleDetection
        function onUserActivity() {
            idleTimer.restart()
            window.hideSaver()
        }
    }

    Timer {
        id: idleTimer
        interval: 30000; running: true; repeat: false
        onTriggered: {
            viewer.hidePopup()
            window.showSaver()
        }
    }

    function hideSaver()
    {
        screenSaver.visible = false
        toolBar.visible = true
    }

    function showSaver()
    {
        toolBar.visible = false
        screenSaver.visible = true
        menuOverlay.visible = false
    }

    header: Rectangle {
        z: 2000
        id: toolBar
        height: toolButton.implicitHeight
        width: parent.width
        color: "#000000"
        ToolButton {
            id: toolButton
            text: "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                menuOverlay.visible = true
            }
        }

        Label {
            font.pixelSize: 16
            color: "#ffffff"
            //text: mainSwipeView.currentItem.title
            verticalAlignment: Text.AlignTop
            anchors.centerIn: parent
        }

        Clock {
            id: clock
            transformOrigin: Item.TopLeft
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: parent.top
        }
    }

    // ========================================
    // LEFT EDGE SWIPE DETECTOR
    // ========================================
    // Invisible MouseArea on the left edge to detect swipe gestures
    MouseArea {
        id: leftEdgeDetector
        width: 50  // 50px wide touch zone on left edge
        height: parent.height
        anchors.left: parent.left
        z: 1000  // Below menuOverlay but above content

        property real startY: 0
        property real startX: 0

        onPressed: {
            startX = mouseX
            startY = mouseY
        }

        onReleased: {
            var deltaX = mouseX - startX
            var deltaY = Math.abs(mouseY - startY)

            // If swiped right more than 100px and vertical movement is less than horizontal
            if (deltaX > 100 && deltaY < deltaX * 0.5) {
                menuOverlay.visible = true
            }
        }
    }

    SwipeView {
        id: mainSwipeView
        //anchors.rightMargin: -222
        anchors.fill: parent
        interactive: false
        transitions: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.InOutQuad }
        }
        Weather {}
        Sensors {}
        System { window: window }
        ViewUpstairs {
            id: viewer
            saverid: screenSaver
        }
        Pond {}
        Cameras {}
        Media {}
        Schedules {}
        PondSettings {}
    }

    // Semi-transparent centered menu overlay with blur
    Rectangle {
        id: menuOverlay
        anchors.fill: parent
        color: "transparent"
        visible: false
        z: 1500

        // Track which menu is visible (main or settings)
        property bool showingSettings: false

        // Blur effect on the background
        FastBlur {
            anchors.fill: parent
            source: mainSwipeView
            radius: 64
            visible: menuOverlay.visible
        }

        // Dark overlay
        Rectangle {
            anchors.fill: parent
            color: "#80000000"  // Semi-transparent black
        }

        // Close menu when clicking outside the menu box
        MouseArea {
            anchors.fill: parent
            onClicked: {
                menuOverlay.visible = false
                menuOverlay.showingSettings = false
            }

            // Support swipe-left to close
            property real startX: 0
            property real startY: 0

            onPressed: {
                startX = mouseX
                startY = mouseY
            }

            onReleased: {
                var deltaX = mouseX - startX
                var deltaY = Math.abs(mouseY - startY)

                // If swiped left more than 100px
                if (deltaX < -100 && deltaY < Math.abs(deltaX) * 0.5) {
                    menuOverlay.visible = false
                    menuOverlay.showingSettings = false
                }
            }
        }

        // Centered MAIN menu container
        Rectangle {
            id: menuContainer
            width: 1000
            height: 600
            anchors.centerIn: parent
            color: "#cc000000"  // Darker semi-transparent background
            radius: 20
            border.color: "#555555"
            border.width: 2
            visible: !menuOverlay.showingSettings

            // Prevent clicks from passing through to background
            MouseArea {
                anchors.fill: parent
                onClicked: {}  // Consume the click
            }

            // Grid layout for menu buttons (3 columns)
            Grid {
                id: menuGrid
                anchors.centerIn: parent
                columns: 4
                rowSpacing: 60
                columnSpacing: 120
                width: parent.width - 10

                property real buttonWidth: 150 //((width - columnSpacing * (columns - 1)) / columns) - 150
                property real buttonHeight: buttonWidth

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: houseImg
                                source: "file:" + applicationDirPath + ".smah/assets/house.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: parent
                                source: houseImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("House")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(3)
                        menuOverlay.visible = false
                    }
                }


                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: pondImg
                                source: "file:" + applicationDirPath + ".smah/assets/fish.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: parent
                                source: pondImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Pond")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(4)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: weatherImg
                                source: "file:" + applicationDirPath + ".smah/assets/cloud.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: parent
                                source: weatherImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Weather")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(0)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: mediaImg
                                source: "file:" + applicationDirPath + ".smah/assets/music.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: parent
                                source: mediaImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Media")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(6)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: temperatureImg
                                source: "file:" + applicationDirPath + ".smah/assets/temperature-full.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: temperatureImg
                                source: temperatureImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Environment")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(1)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: cameraImg
                                source: "file:" + applicationDirPath + ".smah/assets/camera.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: cameraImg
                                source: cameraImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Cameras")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(5)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: statusImg
                                source: "file:" + applicationDirPath + ".smah/assets/info.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: statusImg
                                source: statusImg
                            }

                        }
                        SMAHLabel {
                            text: qsTr("System Info")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(2)
                        menuOverlay.visible = false
                    }
                }

                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: settingsImg
                                source: "file:" + applicationDirPath + ".smah/assets/gears.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: settingsImg
                                source: settingsImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Settings")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        menuOverlay.showingSettings = true
                    }
                }
            }
        }

        // Centered SETTINGS menu container
        Rectangle {
            id: settingsContainer
            width: 1200
            height: 600
            anchors.centerIn: parent
            color: "#cc000000"  // Darker semi-transparent background
            radius: 20
            border.color: "#555555"
            border.width: 2
            visible: menuOverlay.showingSettings

            // Prevent clicks from passing through to background
            MouseArea {
                anchors.fill: parent
                onClicked: {}  // Consume the click
            }

            // Grid layout for settings buttons (3 columns, same structure)
            Grid {
                id: settingsGrid
                anchors.centerIn: parent
                columns: 3
                rowSpacing: 60
                columnSpacing: 120
                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: pondCalImg
                                source: "file:" + applicationDirPath + ".smah/assets/glass-water-droplet.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: pondCalImg
                                source: pondCalImg
                            }

                        }
                        SMAHLabel {
                            text: qsTr("Pond Calibration")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(8)
                        menuOverlay.visible = false
                    }
                }


                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            Image {
                                id: scheduleImg
                                source: "file:" + applicationDirPath + ".smah/assets/clock.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: scheduleImg
                                source: scheduleImg
                            }

                        }
                        SMAHLabel {
                            text: qsTr("Schedules")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        mainSwipeView.setCurrentIndex(7)
                        menuOverlay.visible = false
                    }
                }


                SMAHMenuButton {
                    width: 150
                    height: 150
                    Column {
                        anchors.centerIn: parent
                        spacing: 10
                        Item {
                            width: 100
                            height: 100
                            anchors.horizontalCenter: parent.horizontalCenter
                            Image {
                                id: backImg
                                source: "file:" + applicationDirPath + ".smah/assets/arrow-left.svg"
                                anchors.fill: parent
                            }
                            ColorOverlay {
                                color: "white"
                                anchors.fill: parent
                                source: backImg
                            }
                        }
                        SMAHLabel {
                            text: qsTr("Main Menu")
                            font.pixelSize: 18
                            anchors.horizontalCenter: parent.horizontalCenter
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                    onClicked: {
                        menuOverlay.showingSettings = false
                    }
                }
            }
        }
    }

    ScreenSaver {
        id: screenSaver
        Component.onCompleted: mainSwipeView.setCurrentIndex(3)
    }
}