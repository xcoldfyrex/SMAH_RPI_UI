import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtQml.Models 2.2


Page {
    id: weatherSunCalc
    title: "Weather"
    SMAHBackground {}
    Rectangle {
         width: 150
         height: 150
         color: "transparent"
         border.color: "black"
         border.width: 20
         radius: width*0.5
         SMAHLabel {
              anchors.fill: parent
              text: "Boom"
         }
    }
}
