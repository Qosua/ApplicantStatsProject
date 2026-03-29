import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

SplitView {

    orientation: Qt.Horizontal
    handle: Rectangle {

        implicitWidth: 3

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

        border.color: "#434343"
        border.width: 1

        color: "#191a1c"
        topLeftRadius: 10
        bottomLeftRadius: 10

    }

    Rectangle {
        id: test
        SplitView.preferredWidth: parent.width / (3 / 4)
        SplitView.minimumWidth: parent.width / 10

        border.color: "#434343"
        border.width: 1

        color: "#191a1c"
        topRightRadius: 10
        bottomRightRadius: 10

    }

}