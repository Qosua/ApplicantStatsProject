import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Rectangle {
    id: statusBar

    height: 30
    color: "#26282b"

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    anchors.leftMargin: 15
    anchors.rightMargin: 15
    anchors.topMargin: 5

    Text {
        text: "Путь:  C: > some > very > long > path > to > data > table.xlsx"
        font.pointSize: 11
        color: "#aaaaaa"

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

    }

    Text {
        text: "Версия: 0.8.0"
        font.pointSize: 11
        color: "#aaaaaa"

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

    }

}