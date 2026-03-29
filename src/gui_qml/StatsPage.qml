import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

SplitView {

    orientation: Qt.Horizontal
    handle: Rectangle {
        implicitWidth: 6
        implicitHeight: 6
        color: SplitHandle.hovered ? "steelblue" : "#26282b"
    }

    Rectangle {
        SplitView.preferredWidth: parent.width / 3
        SplitView.minimumWidth: parent.width / 10

        border.color: "#3e3e3e"
        border.width: 1

        color: "#191a1c"
        radius: 10

    }

    Rectangle {
        id: test
        SplitView.preferredWidth: parent.width / (2 / 3)
        SplitView.minimumWidth: parent.width / 10

        border.color: "#3e3e3e"
        border.width: 1

        color: "#191a1c"
        radius: 10

    }

}