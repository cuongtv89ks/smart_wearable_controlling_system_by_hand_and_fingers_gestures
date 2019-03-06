import QtQuick 2.0
import QtQuick.Layouts 1.3

Item {
    id: forecast
    width: 100
    height: 150

    property string day: "N/A"
    property string date: "N/A"
    property string weatherIcon: "N/A"
    property string degree: "N/A"

    ColumnLayout {
        x: 0
        y: 0
        width: 100
        height: 150

        Text{
            id: dayText
            horizontalAlignment: Text.AlignHCenter
            width: forecast.width
            color: "#ffffff"
            text: forecast.day
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            font.bold: true
            font.pointSize: 13
        }

        Text{
            id: dateText
            horizontalAlignment: Text.AlignHCenter
            width: forecast.width
            color: "#ffffff"
            text: forecast.date
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            font.bold: true
            font.pointSize: 12

        }

        WeatherIcon {
            id: weather
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 70
            Layout.preferredWidth: 70
            weatherIcon: forecast.weatherIcon
        }

        Text{
            id: degreeText
            horizontalAlignment: Text.AlignHCenter
            width: forecast.width
            color: "#ffffff"
            text: forecast.degree
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.bold: true
            font.pointSize: 13
        }
    }
}
