import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Window {
    id: window
    width: 1280
    height: 720
    minimumWidth: 320
    minimumHeight: 200

    visible: true
    color: "#26282b"
    title: "UntitledProject"


    // pages menu
    Rectangle {
        id: pagesMenu
        width: 35
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 10
        anchors.topMargin: 10
        color: "#26282b"

        ColumnLayout {
            anchors.fill: parent
            spacing: 10


            PageButton {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.width
                Layout.alignment: Qt.AlignHCenter

                iconSource: "qrc:/resources/icons/stats.png"
            }
            PageButton {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.width
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                iconSource: "qrc:/resources/icons/settings.png"
            }
            Rectangle {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height
                color: "transparent"
            }

        }
    }

    // pages
    StackLayout {
        id: pagesStack

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: pagesMenu.right
        anchors.margins: 10

        StatsPage {
            id: splitView
        }
    }
}



