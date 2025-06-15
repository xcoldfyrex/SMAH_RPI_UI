import QtQuick 2.0
import QtQuick.Controls.Material 2.12

Rectangle {
    z: -9000
    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    id: rectangle
    objectName: "background"
    //left: 0
    x: 0
    y: 0
    width: window.width
    height: window.height
    color: "#1f2024"
    //Image {
//        visible: true
//        fillMode: Image.Stretch
//        source: "file:///" + applicationDirPath + "/.smah/assets/background.png";
//        anchors.fill: parent;
//    }
}
