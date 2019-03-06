import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

Item {
    id: alarm
    anchors.right: parent.right
    anchors.left: parent.left
    width: 250
    height: 139

    property string alarmSet: hour.currentIndex.toString() + ":" +
                              minute.currentIndex.toString() + " " +
                              ap.text;
    property bool isAlarmSetted: sw.checked
    signal dismissButtonClicked
    signal toggled

    RowLayout {
        id: alamSet
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 64
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        visible: true
        opacity: 0.3

        Rectangle {
            id: spinner1
            color: "black"
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 80
            radius: 15
            ListView {
                id: hour
                anchors.fill: parent
                highlightRangeMode: ListView.StrictlyEnforceRange
                preferredHighlightBegin: height/3
                preferredHighlightEnd: height/3
                clip: true
                model: 13
                delegate: Text {
                    font.pixelSize: 30
                    color: "white"
                    text: index
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle {
                anchors.fill: parent
                radius: 15
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FF000000" }
                    GradientStop { position: 0.2; color: "#00000000" }
                    GradientStop { position: 0.8; color: "#00000000" }
                    GradientStop { position: 1.0; color: "#FF000000" }
                }
            }
        }

        Text {
            id: colon
            text: ":"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            color: "white"
            font.bold: true
            font.pixelSize: 70
        }

        Rectangle {
            id: spinner2
            color: "black"
            Layout.preferredHeight: 80
            Layout.preferredWidth: 80
            radius: 15
            ListView {
                id: minute
                anchors.fill: parent
                highlightRangeMode: ListView.StrictlyEnforceRange
                preferredHighlightBegin: height/3
                preferredHighlightEnd: height/3
                clip: true
                model: 60
                delegate: Text {
                    font.pixelSize: 30
                    color: "white"
                    text: index
                    anchors.horizontalCenter: parent.horizontalCenter
                }
            }

            Rectangle {
                id: rectangle
                anchors.fill: parent
                radius: 15
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FF000000" }
                    GradientStop { position: 0.2; color: "#00000000" }
                    GradientStop { position: 0.8; color: "#00000000" }
                    GradientStop { position: 1.0; color: "#FF000000" }
                }
            }
        }

        Text {
            id: ap
            color: "#ffffff"
            text: qsTr("am")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 51
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 22
            states: [
                State {
                    name: "am"
                    PropertyChanges {
                        target: ap
                        text: "am"
                    }
                },
                State {
                    name: "pm"
                    PropertyChanges {
                        target: ap
                        text: "pm"
                    }
                }
            ]

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.state = (parent.state == "am" ? "pm" : "am")
                }
            }
        }
    }

    Switch {
        id: sw
        y: 104
        width: 140
        height: 40
        text: qsTr("Set Alarm")
        anchors.leftMargin: 0
        anchors.left: parent.left
        font.bold: true
        font.pointSize: 12
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -5
        enabled: true
        checked: false
        onToggled: {
            parent.toggled()
            if (sw.checked){
                alamSet.opacity = 1
                //dismissButton.enabled = true
                dismissButton.opacity = 1
            }
            else {
                dismissButton.opacity = 0.3
                //alamSet.enabled = false
                alamSet.opacity = 0.3
            }
        }
    }

    Button {
        id: dismissButton
        y: 104
        height: 45
        text: qsTr("Dismiss")
        anchors.bottomMargin: -10
        anchors.leftMargin: 6
        anchors.left: sw.right
        anchors.right: parent.right
        anchors.rightMargin: 4
        anchors.bottom: parent.bottom
        font.bold: true
        enabled: false
        onClicked: {
            parent.dismissButtonClicked()
        }
    }

}
