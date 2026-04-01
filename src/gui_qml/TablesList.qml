import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Rectangle {

    Rectangle {
        id: buttonsBar
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left

        width: 40
        color: "transparent"
        bottomLeftRadius: 10


    }

    Rectangle {
        id: someKindOfBorder
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: buttonsBar.right
        anchors.topMargin: 1
        anchors.bottomMargin: 1
        color: "#2e2e2e"
        width: 1
    }

    Rectangle {
        id: view
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: someKindOfBorder.right
        anchors.margins: 10
        color: "transparent"

        ListView {

            model: 20
            spacing: 1
            clip: true

            anchors.fill: parent
            anchors.margins: 4
            anchors.horizontalCenter: parent.horizontalCenter

            delegate: Rectangle {
                width: parent.width
                height: 27
                color: "red"
                radius: 8
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}