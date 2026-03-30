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
        anchors.right: someKindOfBorder.left

        width: 50
        color: "transparent"
        bottomLeftRadius: 10


    }

    Rectangle {
        id: someKindOfBorder
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: someKindOfBorder.right
        anchors.right: view.left
        color: "#2e2e2e"
        width: 1
        anchors.margins: 1
        anchors.leftMargin: 0
        anchors.rightMargin: 0
    }

    Rectangle {
        id: view
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 10
        width: parent.width - 51
        color: "transparent"

        ListView {

            model: 4

            anchors.fill: parent
            anchors.margins: 4
            anchors.horizontalCenter: parent.horizontalCenter

            delegate: Rectangle {
                width: parent.width
                height: 30
                color: "red"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}