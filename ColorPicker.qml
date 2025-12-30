import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light 1.0
import smah.zone 1.0

import "SMAHComponents/"

Item {
    property Light device
    property Zone zone
    property string rgb_palette: "file:" + applicationDirPath + ".smah/assets/palette.png"
    property string daylight_palette: "file:" + applicationDirPath + ".smah/assets/color-temperature.png"
    property string f_palette: rgb_palette
    property bool previewReady: false
    property var parentObject

    id: colorPicker
    width: parent.width
    height: parent.height

    function toHex(d) {
        return  ("0"+(Number(d).toString(16))).slice(-2).toUpperCase()
    }

    function getRGB()
    {
        previewReady = true
        var ctx = canvas.getContext("2d")
        var ctx_preview = preview.getContext("2d")
        var id = ctx.getImageData(mouseArea.mouseX, mouseArea.mouseY, 1, 1)
        ctx_preview.strokeStyle = Qt.rgba(id.data[0] /256, id.data[1] /256, id.data[2] /256, 1)

        ctx_preview.fillStyle = Qt.rgba(id.data[0]/256, id.data[1]/256, id.data[2]/256, 1)
        ctx_preview.fillRect(0, 0, preview.width, preview.height);
        ctx_preview.strokeStyle = "#24d12e";

        ctx_preview.fillText("Canvas!",0,0);
        preview.requestPaint();
        var vals = []
        vals['r'] = toHex(id.data[0]);
        vals['g'] = toHex(id.data[1]);
        vals['b'] = toHex(id.data[2]);
        return (vals);
    }
    Image {
        id: loader
        source: f_palette
    }

    Canvas {
        id: canvas
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        width: loader.width
        height: loader.height
        onPaint: {
            var ctx = getContext("2d")
            if (canvas.isImageLoaded(f_palette)) {
                var im = ctx.createImageData(f_palette);
                ctx.drawImage(im, 0, 0)
            }
        }
        Component.onCompleted:loadImage(f_palette);
        onImageLoaded:requestPaint();

        MouseArea {
            id: mouseArea
            anchors.fill: canvas
            onReleased: {
                var col = getRGB()
                device.setColor(col['r']+col['g']+col['b']+toHex(wls.value))
                //element.text = zone.getName + " > " + device.getName + " " + col['r']+col['g']+col['b']+toHex(wls.value)
            }
            onClicked: {
                var col = getRGB()
                //element.text = zone.getName + " > " + device.getName + " " + col['r']+col['g']+col['b']+toHex(wls.value)
            }
        }
    }
    Canvas {
        id: preview
        height: 200
        contextType: qsTr("")
        width: 200
        anchors.top: canvas.top
        anchors.topMargin: 0
        anchors.right: wl.left
        anchors.leftMargin: 0
        onPaint: {
            if (previewReady === false)
            {
                var ctx = getContext("2d")
                //ctx.fillStyle = Qt.rgba(0, 0, 0, 1)
                //ctx.fillRect(0, 0, preview.width, preview.height)
            }
        }
    }


    SMAHLabel {
        id: wl
        text: "White Level: " + toHex(wls.value)
        font.pixelSize: 18
        anchors {
            right: parent.right
            top: canvas.top
        }
    }

    Slider {
        anchors.right: parent.right
        anchors.top: wl.bottom
        height: 400
        id: wls
        orientation: Qt.Vertical
        to: 255
        stepSize: 1
        onMoved: {
            var vals = getRGB()
            device.setColor(vals['r']+vals['g']+vals['b']+toHex(wls.value))
        }



        handle: Rectangle {
            y: wls.topPadding + wls.visualPosition * (wls.availableHeight - height)
            x: wls.leftPadding + wls.availableWidth / 2 - width / 2
            implicitWidth: 96
            implicitHeight: 25
            color: wls.pressed ? "#f0f0f0" : "#f6f6f6"
            border.color: "#bdbebf"
        }
        /*
        handle: Rectangle {
                x: wls.leftPadding + wls.visualPosition * (wls.availableWidth - width)
                y: Math.max(wls.topPadding, wls.availableHeight - height + wls.topPadding - ((wls.availableHeight - height) * (wls.position * 2)))
                width: 15
                height: 30
                radius: 5
                color: 'blue'
            }
            */
    }


    SMAHButton {
        id: close
        text: "Close"
        onClicked: {
            colorPicker.visible = false
            parentObject.visible = true
            element.text = zone.getName
        }
        anchors{
            left: parent.left
            bottom: parent.bottom
        }
        anchors.leftMargin: 100
    }
    SMAHButton {
        id: change
        text: "Change Palette"
        onClicked: {
            canvas.unloadImage(f_palette)
            var ctx = canvas.getContext("2d")
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            if (f_palette === rgb_palette)
            {
                f_palette = daylight_palette
            } else {
                f_palette = rgb_palette
            }
            canvas.loadImage(f_palette)
        }
        anchors{
            left: close.right
            bottom: parent.bottom
        }
        anchors.leftMargin: 100
    }
    SMAHButton {
        id: reset
        text: "Reset"
        anchors.leftMargin: 30
        onClicked: {
            wls.decrease(255)
            device.setColor("00000000")
        }
        anchors {
            left: change.right
            bottom: close.bottom
        }
    }

}

/*##^##
Designer {
    D{i:2;anchors_x:120;anchors_y:54}
}
##^##*/
