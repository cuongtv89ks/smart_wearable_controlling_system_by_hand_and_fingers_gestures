import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Rectangle {
    id: slideBar
    width: 250
    height: 480
    color: "#191919"

    signal predictionChanged
    signal dataChanged

    property string gesturePrediction: bluetoothConnection.gesturePrediction
    property string readData: bluetoothConnection.readData

    Text {
        color: "#ff2b00"
        text: "Smart Home"
        anchors.right: parent.right
        anchors.rightMargin: 126
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        font.pointSize: 22
    }

    TimeDisplay {
        id: timeDisplay
        height: 230
        anchors.rightMargin: 0
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 57
        anchors.left: parent.left
        anchors.right: parent.right
    }

    BluetoothConnection {
        id: bluetoothConnection
        x: 0
        anchors.top: timeDisplay.bottom
        anchors.topMargin: 15
        onGesturePredictionChanged: {
            slideBar.gesturePredictionChanged()
            slideBar.gesturePrediction = bluetoothConnection.gesturePrediction
        }
        onSmartHomeReadDataChanged: {
            slideBar.dataChanged()
            slideBar.readData = bluetoothConnection.readData
        }
    }

    ControlMode {
        id: controlMode
        y: 435
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
    }

}
