import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Item {
    id: item1
    width: 250
    height: 75

    ComboBox {
        id: comboBox
        x: 10
        model: ["Hand Gesture", "Voice Command", "Normal"]
        y: -6
        font.bold: true
        font.pointSize: 12
        anchors.bottomMargin: 5
        anchors.bottom: parent.bottom
        textRole: ""
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.left: parent.left
    }

    Label {
        id: label
        width: 108
        text: qsTr("Control Mode")
        font.bold: true
        anchors.bottom: comboBox.top
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 0
        font.pointSize: 12
        anchors.left: parent.left
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

}
