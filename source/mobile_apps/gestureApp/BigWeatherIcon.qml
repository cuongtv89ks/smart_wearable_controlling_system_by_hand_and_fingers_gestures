import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    anchors.top: parent.top
    anchors.topMargin: 10
    anchors.left: parent.left
    anchors.leftMargin: 10
    anchors.right: parent.right
    anchors.rightMargin: 10

    id: bigWeatherIcon

    property string weatherIcon: ""
    property string humidity: "?"
    property string windSpeed: "?"
    property string pressure: "?"
    property string visibility: "?"
    property string location: "?"
    property string condition: "?"
    property string degree: "?"
    property string sunrise: "?"
    property string sunset: "?"

    RowLayout {
        anchors.top: parent.top
        anchors.topMargin: 144
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10
        clip: false

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Image {
                id: image5
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/sunrise.png"
            }

            Text {
                id: text9
                color: "#ffffff"
                text: qsTr("sunrise")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: sunrise
                color: "#ffffff"
                text: bigWeatherIcon.sunrise
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Image {
                id: image4
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/sunset.png"
            }

            Text {
                id: text8
                color: "#ffffff"
                text: qsTr("sunset")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: sunset
                color: "#ffffff"
                text: bigWeatherIcon.sunset
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            Image {
                id: image
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/humidity.png"
            }

            Text {
                id: text4
                color: "#ffffff"
                text: qsTr("humidity")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: humidity
                color: "#ffffff"
                text: bigWeatherIcon.humidity + qsTr(" %")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Image {
                id: image1
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/wind.png"
            }

            Text {
                id: text5
                color: "#ffffff"
                text: qsTr("wind")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: wind
                color: "#ffffff"
                text: bigWeatherIcon.windSpeed + qsTr(" mph")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Image {
                id: image2
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/pressure.png"
            }

            Text {
                id: text6
                color: "#ffffff"
                text: qsTr("pressure")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: pressure
                color: "#ffffff"
                text: bigWeatherIcon.pressure + qsTr(" in")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true

            Image {
                id: image3
                Layout.preferredHeight: 50
                Layout.preferredWidth: 50
                source: "images/icons/visibility.png"
            }

            Text {
                id: text7
                color: "#ffffff"
                text: qsTr("visib")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }

            Text {
                id: visibility
                color: "#ffffff"
                text: bigWeatherIcon.visibility + qsTr(" mi")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.preferredWidth: 50
                font.pixelSize: 12
            }
        }
    }

    RowLayout {
        height: 125
        anchors.right: parent.right
        anchors.rightMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 10

        ColumnLayout {
            Layout.preferredHeight: 125
            Layout.preferredWidth: 186

            Text {
                id: location
                color: "#ffffff"
                text: bigWeatherIcon.location
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 41
                Layout.preferredWidth: 161
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 35
            }

            Text {
                id: condition
                color: "#ffffff"
                text: bigWeatherIcon.condition
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.preferredHeight: 41
                Layout.preferredWidth: 186
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 25
            }
        }

        WeatherIcon {
            weatherIcon: bigWeatherIcon.weatherIcon
            id: icon
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 125
            Layout.preferredWidth: 160
        }

        Text {
            id: degree
            color: "#ffffff"
            text: bigWeatherIcon.degree + qsTr("°C")
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 78
            Layout.preferredWidth: 104
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 35
        }
    }

}
