import QtQuick 2.0
import QtQuick.Controls.Material 2.12

Rectangle {
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    id: rectangle
    objectName: "background"
    width: window.width
    height: window.height
    color: "#868f96"

    border.width: 0
    Image { source: "file:////home/lenny/.smah/assets/background.png"; fillMode: Image.scale; anchors.fill: parent; }
}
