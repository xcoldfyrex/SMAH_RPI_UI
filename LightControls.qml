import QtQuick 2.0
import QtQuick.Controls 2.5
import smah.light 1.0


SMAHBackground {
    property int light_type: 0
    property int light_id: 0
    SMAHLabel
    {
        text: Light.getName()
    }

}
