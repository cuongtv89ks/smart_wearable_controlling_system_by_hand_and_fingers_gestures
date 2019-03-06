import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    id: weather
    anchors.fill: parent

    property string currentCondition: bigWeatherIcon.weatherIcon
    property string currentTemperature: bigWeatherIcon.degree

    function query(woeid){
        var url = 'https://query.yahooapis.com/v1/public/yql?q=select * from weather.forecast where woeid= ' + woeid + '&format=json'
        var res
        var doc = new XMLHttpRequest()
        doc.onreadystatechange = function() {
            if (doc.readyState === XMLHttpRequest.DONE) {
                res = doc.responseText
                parseJSON(res)
                //console.log(res)
            }
        }
        doc.open('GET', url, true)
        doc.send()
    }

    function parseJSON(data) {
        var obj = JSON.parse(data)
        if (typeof(obj) === 'object'){
            if (obj.hasOwnProperty('query')){
                var ch = obj.query.results.channel
                var day = [], date = [], high = [], low = [], condition = [], bigCondition = ''
                for (var fk in ch.item.forecast){
                    day.push(ch.item.forecast[fk].day)
                    date.push(ch.item.forecast[fk].date)
                    high.push(Math.floor((ch.item.forecast[fk].high -32) * 5 / 9))
                    low.push(Math.floor((ch.item.forecast[fk].low -32) * 5 / 9))
                    condition.push((ch.item.forecast[fk].text).toLowerCase())
                }

                bigCondition = (ch.item.condition.text)
                bigCondition = bigCondition.toLowerCase()

                bigWeatherIcon.location = ch.location.city
                bigWeatherIcon.degree = Math.floor((ch.item.condition.temp -32) * 5 / 9)
                bigWeatherIcon.windSpeed = ch.wind.speed
                bigWeatherIcon.weatherIcon = bigCondition
                bigWeatherIcon.humidity = ch.atmosphere.humidity
                bigWeatherIcon.pressure = ch.atmosphere.pressure
                bigWeatherIcon.visibility = ch.atmosphere.visibility
                bigWeatherIcon.sunrise = ch.astronomy.sunrise
                bigWeatherIcon.sunset = ch.astronomy.sunset
                bigWeatherIcon.condition = bigCondition

                forecastIcon.day = day[0]
                forecastIcon.date = date[0]
                forecastIcon.degree = String(high[0]) + "°/" + String(low[0]) + "°"
                forecastIcon.weatherIcon = String(condition[0])

                forecastIcon1.day = day[1]
                forecastIcon1.date = date[1]
                forecastIcon1.degree = String(high[1]) + "°/" + String(low[1])+ "°"
                forecastIcon1.weatherIcon = String(condition[1])

                forecastIcon2.day = day[2]
                forecastIcon2.date = date[2]
                forecastIcon2.degree = high[2] + "°/" + low[2]+ "°"
                forecastIcon2.weatherIcon = String(condition[2])

                forecastIcon3.day = day[3]
                forecastIcon3.date = date[3]
                forecastIcon3.degree = high[3] + "°/" + low[3] + "°"
                forecastIcon3.weatherIcon = String(condition[3])

                forecastIcon4.day = day[4]
                forecastIcon4.date = date[4]
                forecastIcon4.degree = high[4] + "°/" + low[4] + "°"
                forecastIcon4.weatherIcon = String(condition[4])

            }
        }
    }

    Timer {
        interval: 10; running: true; repeat: false
        onTriggered: weather.query(1132466)
    }

    Timer {
        interval: 600000; running: true; repeat: true
        onTriggered: weather.query(1132466)
    }

    BackGround {
        id: backGround
        anchors.fill: parent

        Item {
            id: item1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 40
            anchors.topMargin: 10
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.rightMargin: 25
            anchors.leftMargin: 25

            Rectangle {
                id: rectangle
                anchors.fill: parent
                opacity: 0.35
                color: "black"
                radius: 20

            }

            BigWeatherIcon {
                id: bigWeatherIcon
                height: 234
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.topMargin: 10
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
            }

            RowLayout {
                anchors.top: bigWeatherIcon.bottom
                anchors.topMargin: 5
                spacing: 8
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10

                ForecastIcon {
                    id: forecastIcon
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }

                ForecastIcon {
                    id: forecastIcon1
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }

                ForecastIcon {
                    id: forecastIcon2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                ForecastIcon {
                    id: forecastIcon3
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                ForecastIcon {
                    id: forecastIcon4
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: {
            weather.query(1132466)
        }
    }
}
