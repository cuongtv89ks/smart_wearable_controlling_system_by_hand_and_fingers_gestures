import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import io.qt.myassistant 1.0
import io.qt.mymediaplayer 1.0
import io.qt.myrecognition 1.0
import io.qt.smarthome 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 800
    height: 480
    title: qsTr("Smart Home")

    MyAssistant {
        id: myAssistant
    }

    MyMediaPlayer {
        id: player
    }

    MyRecognition {
        id: recognition
        onIsSocketConnectedChanged: {
            if(isSocketConnected){
                bluetoothConnection.setControllerPicOpacity(1)
            } else {
                bluetoothConnection.setControllerPicOpacity(0.3)
            }
        }
        onPredictionChanged: {
            if (prediction === "Right"){
                tabBar.currentIndex += 1
                if (tabBar.currentIndex > 2){
                    tabBar.currentIndex = 0
                }
            }
            else if (prediction === "Left"){
                tabBar.currentIndex -= 1
                if (tabBar.currentIndex < 0){
                    tabBar.currentIndex = 2
                }
            }
            else if (prediction === "W"){
                player.setPlayMusicMedia("/weather/rain-thunder.mp3")
                player.playMusic()
                myAssistant.speak("Today, the weather in Daegu is " +
                                  weather.currentCondition +
                                  "and the temperature is " +
                                  weather.currentTemperature)
                tabBar.currentIndex = 2

            }
            else if (prediction === "M"){
                player.setPlayMusicMedia("/music/test.mp3")
                player.playMusic()
            }
            else if (prediction === "S"){
                player.stopPlayMusic()
            }
            else if (prediction === "Up"){
                //turn on light
                console.log("turn on the lamp")
                smartHome.sendMessage("h")
                lights.setReadingLightChecked(true)
                //smartHome.sendMessage()
            }
            else if (prediction === "Down"){
                // turn off the light
                console.log("turn off the lamp")
                smartHome.sendMessage("b")
                lights.setReadingLightChecked(false)
            }
            else if (prediction === "Rotate_right"){
                // bright up the lamp
                console.log("bright up the lamp")
                smartHome.sendMessage("u")
            }
            else if (prediction === "Rotate_left"){
                console.log("bright down the lamp")
                smartHome.sendMessage("d")
            }
        }
    }

    SmartHome {
        id: smartHome
        onIsSocketConnectedChanged: {
            if(isSocketConnected){
                bluetoothConnection.setSmartDevicesPicOpacity(1)
            } else {
                bluetoothConnection.setControllerPicOpacity(0.3)
            }
        }
        onReadDataChanged: {
            sensors.temperature = readData
        }
    }

    StackLayout {
        id: swipeView
        anchors.left: slideBar.right
        anchors.right: parent.right
        anchors.bottom: tabBar.bottom
        anchors.top: parent.top
        currentIndex: tabBar.currentIndex

        LightControl {
            id: lights
            anchors.fill: parent
            onToggleReadingLamp: {
                if (readingLigtChecked){
                    smartHome.sendMessage("h")
                } else {
                    smartHome.sendMessage("b")
                }
            }
        }

        SensorsDisplay {
            id: sensors
            anchors.fill: parent
        }

        WeatherDisplay {
            id: weather
            anchors.fill: parent
        }
    }

    TabBar {
        id: tabBar
        anchors.right: parent.right
        anchors.left: slideBar.right
        anchors.bottom: parent.bottom
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Lights")
        }
        TabButton {
            text: qsTr("Sensor Inf")
        }

        TabButton {
            text: qsTr("Weather")
        }
    }

    Rectangle {
        id: slideBar
        width: 250
        height: 480
        color: "#191919"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom

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
            onControllerSWToggled: {
                if (isControllerSWChecked){
                    recognition.on_gloveConnectButton_clicked()
                } else {
                    recognition.on_gloveDisconnectButton_clicked()
                }
            }
            onSmartDevicesSWToggled:  {
                if (isSmartDevicesSWChecked){
                    smartHome.on_smartHomeSocketConnectButton_clicked()
                } else {
                    smartHome.on_smartHomeSocketDisconnectButton_clicked()
                }
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
}
