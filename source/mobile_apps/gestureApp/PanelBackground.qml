import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.2

Rectangle {
    id: rectangle1
    Material.theme: Material.Dark
    Material.accent: Material.DeepOrange
    width: 550
    height: 480

    color: "#191919"
    clip: true
    property alias title: label.text

    Label {
        id: label
        x: 8
        y: 18
        color: "#eeeeec"
        font.pixelSize: 22
        text: qsTr("")
        font.pointSize: 23
    }

    Rectangle {
        id: rectangle
        x: 492
        width: 100
        height: 74
        color: "#3a3a3a"
        anchors.right: parent.right
        anchors.rightMargin: -42
        anchors.top: parent.top
        anchors.topMargin: -30
        clip: true
        rotation: 45
    }

}
