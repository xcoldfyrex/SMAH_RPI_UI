import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls.Material 2.12

Label {
    Material.theme: Material.Dark
    Material.accent: Material.Purple
    FontLoader {
        id: noto;
        source: "file:" + applicationDirPath + ".smah/assets/NotoSans-Regular.ttf"
    }
    FontLoader {
        id: crescent;
        source: "file:" + applicationDirPath + ".smah/assets/Crescent-Regular.ttf"
    }
    color: "#d4d4d4"
    font.family: crescent.name
}
