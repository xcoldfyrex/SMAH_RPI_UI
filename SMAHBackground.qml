import QtQuick 2.0
import QtQuick.Controls.Material 2.12

Rectangle {
    z: -2000
    visible: true
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    id: rectangle
    objectName: "background"
    width: window.width
    height: window.height
    color: "#868f96"
    Image {
        visible: true
        fillMode: Image.Stretch
        source: "file:///" + applicationDirPath + "/.smah/assets/background.png";
        anchors.fill: parent;
    }
}
