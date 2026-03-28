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


    Rectangle {
        id: pagesBar
        width: 32
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: "#26282b"
    }

    StackLayout {
        id: stackLayout
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: pagesBar.right
        anchors.margins: 10

        StatsPage {
            id: splitView
        }
    }
}



