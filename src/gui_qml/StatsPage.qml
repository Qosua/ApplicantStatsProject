import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

SplitView {

    orientation: Qt.Horizontal
    handle: Rectangle {

        implicitWidth: 4

        color: SplitHandle.hovered ? "#556da3" : "transparent"

        Behavior on color {
            ColorAnimation {
                duration: 100
            }
        }
    }

    Rectangle {

        SplitView.preferredWidth: parent.width / 4
        SplitView.minimumWidth: parent.width / 10

        color: "transparent"
        topLeftRadius: 10
        bottomLeftRadius: 10

        SplitView {

            anchors.fill: parent
            orientation: Qt.Vertical
            handle: Rectangle {

                implicitHeight: 5

                color: SplitHandle.hovered ? "#556da3" : "transparent"

                Behavior on color {
                    ColorAnimation {
                        duration: 100
                    }
                }
            }

            Rectangle {
                color: "#191a1c"
                border.width: 1
                border.color: "#323232"
                topLeftRadius: 10
                SplitView.preferredHeight: parent.height / 2
                SplitView.minimumHeight: parent.height / 10

                FacultyTreeView {
                    anchors.fill: parent
                    anchors.margins: 8
                }
            }

            TablesList {
                color: "#191a1c"
                border.width: 1
                border.color: "#323232"
                bottomLeftRadius: 10
                SplitView.preferredHeight: parent.height / 2
                SplitView.minimumHeight: parent.height / 10


            }
        }
    }

    Rectangle {
        SplitView.preferredWidth: parent.width / (3 / 4)
        SplitView.minimumWidth: parent.width / 10

        border.color: "#323232"
        border.width: 1

        color: "#191a1c"
        topRightRadius: 10
        bottomRightRadius: 10


    }

}