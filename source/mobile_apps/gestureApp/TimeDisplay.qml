import QtQuick 2.0
import io.qt.mydatetime 1.0

Item {
    id: timeDisplay
    width: 250
    height: 250

    MyDateTime {
        id: myDateTime
    }

    Text {
        id: time
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 0
        text: myDateTime.currentTime
        anchors.horizontalCenterOffset: 0
        color: "orange"
        font.pixelSize: 50
    }

    Text {
        id: date
        anchors.top: time.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        text: myDateTime.currentDate
        font.pixelSize: 27
        color: "orange"

    }

    Alarm {
        id: alarm
        anchors.top: date.bottom
        anchors.topMargin: 15
        anchors.bottom: parent.bottom
        onToggled: {
            if(alarm.isAlarmSetted){
                myDateTime.alarmSet = alarm.alarmSet
                myDateTime.activeAlarm();
                myDateTime.setAlarmSound("/music/test.mp3")
            } else {
                myDateTime.disableAlarm();
            }
        }

        onDismissButtonClicked: {
            myDateTime.dismissAlarm()
        }
    }

}
