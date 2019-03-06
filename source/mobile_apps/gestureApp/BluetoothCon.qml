import QtQuick 2.0
//import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import QtBluetooth 5.5

Item {
    id: bluetoothCon
    height: 80
    width: 250

    property bool serviceFound: false
    property string tempSensor: "?"

    BluetoothDiscoveryModel {
        id: btModel
        discoveryMode: BluetoothDiscoveryModel.MinimalServiceDiscovery
        running: false

        onRunningChanged: {
            if (!btModel.running && !serviceFound){
                console.log("No service found")
            }
        }

        onErrorChanged: {
            if (error != BluetoothDiscoveryModel.NoError && !btModel.running) {
                console.log("Failed")
            }
        }

        onServiceDiscovered: {
            if (serviceFound)
                return
            serviceFound = true
            console.log("Found new service " + service.deviceAddress + " " + service.deviceName + " " + service.serviceName);
            socket.setService(service)
        }
        uuidFilter: "00001101-0000-1000-8000-00805F9B34FB"
    }

    BluetoothSocket {
        id: socket
        connected: true
        onSocketStateChanged:  {
            bltIcon.opacity = 1
        }

        onStringDataChanged: {
            console.log("Received data: ")
            var data = socket.stringData;
            data = data.substring(0, data.indexOf('\n'))
            //console.log(data);
            bluetoothCon.tempSensor = data;
        }
    }

    function turnLedOn(){
        socket.stringData = "h";
    }

    function turnLedOff(){
        socket.stringData = "b";
    }

    RadioButton {
        id: bltActive
        y: 16
        text: qsTr("Active Bluetooth")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        onToggled: {
            btModel.running = true
        }
    }

    Image {
        id: bltIcon
        x: 189
        y: 22
        width: 40
        height: 40
        anchors.verticalCenterOffset: 0
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        source: "images/icons/bluetooth.png"
        opacity: 0.3
    }
}
