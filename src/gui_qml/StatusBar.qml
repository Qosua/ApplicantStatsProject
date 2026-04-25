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

    RowLayout {
        anchors.fill: parent
        spacing: 20

        Text {
            id: pathText
            text: (qmlHelper.currentTablePath !== ""
                ? "Путь:  " + qmlHelper.currentTablePath.replace(/[\\/]/g, " > ")
                : "Путь:  файл не выбран")
            font.pointSize: 11
            color: "#cccccc"
            elide: Text.ElideMiddle
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            text: "Версия: " + qmlHelper.appVersion
            font.pointSize: 11
            color: "#cccccc"

        }
    }

}