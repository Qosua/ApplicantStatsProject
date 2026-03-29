import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

function defineColor(hovered, chose) {
    if(chose) {
        return btnChoseBackgroundColor;
    }
    if(hovered)
        return "red"

    return ""

}

Button {
    property bool isButtonChecked: false
    property string iconSource: ""
    property color btnBackgroundColor: "#26282b"
    property color btnChoseBackgroundColor: "#123462"

    flat: true
    icon.source: iconSource
    icon.width: 25
    icon.height: 25
    icon.color: "#BBBBBB"
    antialiasing: true
    hoverEnabled: true

    onClicked: {
        isButtonChecked = !isButtonChecked
    }

    Rectangle {
        anchors.fill: parent
        color:  { return isButtonChecked ? btnHoverBackgroundColor : btnBackgroundColor}
        radius: 8
    }

}