import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
Page {
    Image {
        id: image
        source: "file:" + applicationDirPath + ".smah/assets/F1.svg"
        width: parent.width
        height: parent.height
        fillMode: Image.PreserveAspectFit
        smooth: true
    }
    SMAHBackground {}
    PinchArea
    {
        MouseArea
        {
            id:dragArea
            hoverEnabled: true
            anchors.fill: parent
            drag.target: image
            scrollGestureEnabled: false
            //            drag.maximumX: Screen.width
            //            drag.maximumY: Screen.height

        }
        anchors.fill:image
        enabled: true
        //        pinch.target: image
        pinch.maximumScale: 4.0
        pinch.minimumScale: 1.0
        //pinch.dragAxis: pinch.XandYAxis
        pinch.maximumX: image.width
        pinch.maximumY: image.height
        onPinchStarted: {
            console.log("console ","pinchstarted")
            image.scale = Math.round(pinch.scale / 10) * 10;
        }

        onPinchUpdated: {

            console.log("console ","pinchUpdated")
            image.scale = Math.round(pinch.scale / 10) * 10;
        }
        onPinchFinished: {
            console.log("console ","pinchfinished")
        }
    }

}
