import QtQuick 2.7
import QtQuick.Controls 2.2

Item {
    id: background
    anchors.fill: parent

    property alias soureWallpaper: bgImg.source

    Image {
        anchors.fill: parent
        id: bgImg
        source: background.changeWallPaper()
    }

    function changeWallPaper(){
        var number = Math.floor((Math.random() * 5) + 1);
        soureWallpaper = "images/wallpapers/" + String(number) + ".jpg"
    }

    Timer {
        interval: 50000; running: true; repeat: true;
        onTriggered: background.changeWallPaper()
    }
}
