import QtQuick 2.4
import QtQuick.Layouts 1.0

PanelBackground {
    id: sensorDisplay
    width: 550
    height: 480
    title: "Sensor Information"

    property string temperature: "?"

    ColumnLayout {
        x: 77
        y: 147
        width: 425
        height: 268
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        RowLayout {
            height: 90
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: false
            Layout.fillWidth: true

            Image {
                id: image
                Layout.preferredHeight: 70
                Layout.preferredWidth: 70
                source: "images/icons/temperature.png"
            }

            Text {
                id: tempText
                color: "#ff2b00"
                text: sensorDisplay.temperature + qsTr("°C")
                Layout.preferredHeight: 75
                Layout.preferredWidth: 105
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
            }

            Image {
                id: image2
                Layout.preferredHeight: 70
                Layout.preferredWidth: 70
                source: "images/icons/uv.png"
            }

            Text {
                id: text2
                color: "#ff2b00"
                text: qsTr("3 mW/cm2")
                Layout.columnSpan: 2
                Layout.preferredHeight: 44
                Layout.preferredWidth: 130
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 25
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Image {
                id: image1
                Layout.preferredHeight: 70
                Layout.preferredWidth: 70
                source: "images/icons/humidity.png"
            }

            Text {
                id: text3
                color: "#ff2b00"
                text: qsTr("58%")
                Layout.preferredHeight: 75
                Layout.preferredWidth: 105
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
            }

            Image {
                id: image3
                Layout.preferredHeight: 70
                Layout.preferredWidth: 70
                source: "images/icons/dust.png"
            }

            Text {
                id: text4
                color: "#ff2b00"
                text: qsTr("3 μg")
                Layout.preferredHeight: 75
                Layout.preferredWidth: 105
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 40
            }
        }
    }
}
