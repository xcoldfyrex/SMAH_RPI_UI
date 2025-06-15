var lights
var lightTitles = []

function createLightList(lights, gridParent, id) {
    for (var i=0; i<=lights.length-1; i++) {
        lightTitles[i] = '"' + lights[i].getName + '"'
    }
    console.log(lightTitles)

    var component = Qt.createQmlObject('import QtQuick 2.0;' +
                                       'import QtQuick.Controls 2.5;' +
                                       'import QtQuick.Layouts 1.0;' +
                                       'Repeater {' +
                                       'property var lightTitles: [ ' + lightTitles + ' ];' +
                                       'id: nameReapeter;' +
                                       'model: lightTitles;' +
                                       'Label {' +
                                       'color: "#ffffff";' +
                                       'height: 480;' +
                                       'Layout.row: index;' +
                                       'Layout.column: 0;' +
                                       'Layout.fillWidth: true;' +
                                       'Layout.fillHeight: true;' +
                                       'text: modelData;' +
                                       '}' +
                                       '}',
                                       gridParent,
                                       "dynamicSnippet1" + id);
}

function createWhiteLight(lights, gridParent, id) {
    var component = Qt.createQmlObject('import QtQuick 2.0; import QtQuick.Controls 2.5; import QtQuick.Layouts 1.0; Label {parent:' + gridParent + ';  text:"' + lights.getName + '"}',
                                       gridParent,
                                       "dynamicSnippet1" + id);
    //console.log(component)
}

function createRGBLight() {

}
