import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import smah.light 1.0
import smah.zone 1.0

Page {
    property Light device
    property var rgb_palette: "file:" + applicationDirPath + ".smah/assets/palette.png"
    property var previewReady: false
    width: 800
    height: 800
    visible: false
    id: page

    SMAHBackground {}

    Canvas {
        id: canvas
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        width: 720
        height: 663
        onPaint: {
            var ctx = getContext("2d")
            if (canvas.isImageLoaded(rgb_palette)) {
                var im = ctx.createImageData(rgb_palette);
                ctx.drawImage(im, 0, 0)
            }
        }
        Component.onCompleted:loadImage(rgb_palette);
        onImageLoaded:requestPaint();

        MouseArea {
            id: mouseArea
            anchors.fill: canvas
            onClicked: {
                function toHex(d) {
                    return  ("0"+(Number(d).toString(16))).slice(-2).toUpperCase()
                }

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
                var r = toHex(id.data[0]);
                var g = toHex(id.data[1]);
                var b = toHex(id.data[2]);
                device.setColor(r+g+b+"00")
                console.log(r+g+b+"00")
            }
        }
    }

    Canvas {
        id: preview
        height: 200
        contextType: qsTr("")
        width: 200
        anchors.top: deviceName.top
        anchors.topMargin: 0
        anchors.left: canvas.right
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
        id: deviceName
        text: device.getName
        font.pixelSize: 18
        anchors {
            left: canvas.right
            top: canvas.top
        }
    }

    Button {
        y: 691
        text: "Close"
        anchors.bottomMargin: 76
        anchors.leftMargin: 0
        onClicked: page.visible = false
        anchors {
            left: parent.left
            bottom: parent.bottom
        }
    }
}

/*##^##
Designer {
    D{i:2;anchors_x:120;anchors_y:54}
}
##^##*/
