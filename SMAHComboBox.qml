import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material

import ".."

ComboBox  {
    property var popupHeight: ""
    property int popupWidth: 300
    id: control
    font.pointSize: Style.fontCellSize
    delegate: ItemDelegate {
        width: control.width
        contentItem: Text {
            text: modelData
            color: "white"
            font.pointSize: Style.fontHeaderSize
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
        highlighted: control.highlightedIndex === index
    }

    contentItem: Text {
        text: control.displayText
        font: control.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: popupWidth
        implicitHeight: 40
        radius: 0
        color: "black"
    }

    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: popupHeight
        padding: 1
        contentItem: ListView {
            id: list
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex
            ScrollBar.vertical: SMAHScrollBar { }
            highlight: Rectangle { color: "#12141C"; radius: 5 }
        }
        background: Rectangle {
            color: "black"
        }
    }
    model: []
}
