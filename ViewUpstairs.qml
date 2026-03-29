import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import smah.light 1.0
import smah.zone 1.0
import smah.objectfactory

import "qrc:/SMAHComponents/"
import "qrc:/ZoneComponents"

Item {
    id: viewPage
    property string level: "file:" + applicationDirPath + ".smah/assets/F1.png"
    property var zonePages: [{}]
    property ScreenSaver saverid
    function toHex(d) {
        return  ("0"+(Number(d).toString(16))).slice(-2).toUpperCase()
    }
    function hidePopup(){
        for (const z of zonePages) {
                z.close()
        }
    }

    Component.onCompleted: {
        for (var i=0; i<factory.getZoneObjects().length; i++) {
            var zonecomponent= Qt.createComponent("/ZoneComponents/ZoneOptionsPopup.qml")
            var zoneloadwin = zonecomponent.createObject(viewPage, {zone: factory.getZoneObjects()[i], anchorParent: viewPage} )
            zonePages[i] = zoneloadwin
        }
    }

    SMAHTBox {
        id: box
        Image {
            id: imageBuf
            source: level
            visible: false
        }
        headerText: "Zone Selection"
        Canvas {
            id: image
            width: imageBuf.width
            height: imageBuf.height
            anchors.centerIn: parent
            x: (parent.width - imageBuf.width) / 2
            smooth: true
            onPaint: {
                var ctx = getContext("2d")
                if (image.isImageLoaded(level)) {
                    var im = ctx.createImageData(level);
                    ctx.drawImage(im, 0, 0)
                }
            }
            Component.onCompleted:loadImage(level);
            onImageLoaded:requestPaint();
            MouseArea {
                id: mouseArea
                anchors.fill: image
                onClicked: {
                    var ctx = image.getContext("2d")
                    var id = ctx.getImageData(mouseArea.mouseX, mouseArea.mouseY, 1, 1)
                    var vals = toHex(id.data[0]) + toHex(id.data[1]) + toHex(id.data[2])
                    for (const z of zonePages) {
                        if (z.zone.getCC === vals.toString()) {
                            z.open()
                        }
                    }
                }
            }
        }
    }
}
