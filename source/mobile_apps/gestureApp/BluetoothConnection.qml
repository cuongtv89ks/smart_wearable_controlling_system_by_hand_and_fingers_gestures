import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Item {
    id: bltConnections
    width: 250
    height: 160

    property alias isControllerSWChecked: controllerSW.checked
    property alias isSmartDevicesSWChecked: smartDevicesSW.checked

    signal controllerSWToggled;
    signal smartDevicesSWToggled;

    function setControllerPicOpacity(opa){
        controllerPic.opacity = opa
    }

    function setSmartDevicesPicOpacity(opa){
        smartDevicesPic.opacity = opa
    }

    GroupBox {
        id: groupBox
        font.bold: true
        font.pointSize: 12
        anchors.fill: parent
        title: qsTr("Bluetooth Connections")
        
        Switch {
            id: smartDevicesSW
            y: 66
            text: qsTr("Smart Devices")
            font.bold: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -5
            onToggled: {
                bltConnections.smartDevicesSWToggled()
                if (!smartDevicesSW.checked){
                    smartDevicesPic.opacity = 0.3
                }
            }
        }
        
        Switch {
            id: controllerSW
            text: qsTr("Gesture Device")
            font.bold: true
            anchors.bottom: smartDevicesSW.top
            anchors.bottomMargin: 18
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: -5
            onToggled: {
                bltConnections.controllerSWToggled()
                if (!controllerSW.checked){
                    controllerPic.opacity = 0.3
                }
            }
        }

        Image {
            id: controllerPic
            width: 50
            height: 55
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.topMargin: -4
            anchors.left: controllerSW.right
            anchors.leftMargin: 16
            source: "images/icons/favicon (1).png"
            opacity: 0.3
        }

        Image {
            id: smartDevicesPic
            y: 61
            width: 50
            height: 50
            anchors.rightMargin: 0
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: -3
            anchors.left: smartDevicesSW.right
            anchors.leftMargin: 23
            source: "images/icons/bluetooth.png"
            opacity: 0.3
        }
    }
}
