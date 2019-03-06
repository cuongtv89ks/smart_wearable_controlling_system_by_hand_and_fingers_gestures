import QtQuick 2.0

Item {
    id: container
    property string weatherIcon: ""
    Image {
        id: img
        source: {
            switch (weatherIcon) {
            case "tornado":
                "images/weatherIcons/00.png"
                break;
            case "tropical storm":
                "images/weatherIcons/01.png"
                break;
            case "rain":
                "images/weatherIcons/02.png"
                break;
            case "severe thunderstorms":
                "images/weatherIcons/03.png"
                break;
            case "thunderstorms":
                "images/weatherIcons/04.png"
                break;
            case "mixed rain and snow":
                "images/weatherIcons/05.png"
                break;
            case "mixed rain and sleet":
                "images/weatherIcons/06.png"
                break;
            case "mixed snow and sleet":
                "images/weatherIcons/07.png"
                break;
            case "freezing drizzle":
                "images/weatherIcons/08.png"
                break;
            case "drizzle":
                "images/weatherIcons/09.png"
                break;
            case "freezing rain":
                "images/weatherIcons/10.png"
                break;
            case "showers":
                "images/weatherIcons/11.png"
                break;
            case "showers":
                "images/weatherIcons/12.png"
                break;
            case "snow flurries":
                "images/weatherIcons/13.png"
                break;
            case "light snow showers":
                "images/weatherIcons/14.png"
                break;
            case "blowing snow":
                "images/weatherIcons/15.png"
                break;
            case "snow":
                "images/weatherIcons/16.png"
                break;
            case "hail":
                "images/weatherIcons/17.png"
                break;
            case "sleet":
                "images/weatherIcons/18.png"
                break;
            case "dust":
                "images/weatherIcons/19.png"
                break;
            case "foggy":
                "images/weatherIcons/20.png"
                break;
            case "haze":
                "images/weatherIcons/21.png"
                break;
            case "smoky":
                "images/weatherIcons/22.png"
                break;
            case "blustery":
                "images/weatherIcons/23.png"
                break;
            case "windy":
                "images/weatherIcons/24.png"
                break;
            case "cold":
                "images/weatherIcons/25.png"
                break;
            case "cloudy":
                "images/weatherIcons/26.png"
                break;
            case "mostly cloudy":
                "images/weatherIcons/28.png"
                break;
            case "partly cloudy":
                "images/weatherIcons/30.png"
                break;
            case "clear":
                "images/weatherIcons/31.png"
                break;
            case "sunny":
                "images/weatherIcons/32.png"
                break;
            case "fair":
                "images/weatherIcons/34.png"
                break;
            case "mixed rain and hail":
                "images/weatherIcons/35.png"
                break;
            case "hot":
                "images/weatherIcons/36.png"
                break;
            case "isolated thunderstorms":
                "images/weatherIcons/37.png"
                break;
            case "scattered thunderstorms":
                "images/weatherIcons/38.png"
                break;
            case "scattered thunderstorms":
                "images/weatherIcons/39.png"
                break;
            case "scattered showers":
                "images/weatherIcons/40.png"
                break;
            case "heavy snow":
                "images/weatherIcons/41.png"
                break;
            case "scattered snow showers":
                "images/weatherIcons/42.png"
                break;
            case "heavy snow":
                "images/weatherIcons/43.png"
                break;
            case "partly cloudy":
                "images/weatherIcons/44.png"
                break;
            case "thundershowers":
                "images/weatherIcons/45.png"
                break;
            case "snow showers":
                "images/weatherIcons/46.png"
                break;
            case "isolated thundershowers":
                "images/weatherIcons/47.png"
                break;
            default:
                 "images/weatherIcons/na.png"
        }
        }
        smooth: true
        anchors.fill: parent
    }
}
