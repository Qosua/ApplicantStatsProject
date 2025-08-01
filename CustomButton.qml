import QtQuick 2.15

Rectangle {

    property string btnName
    property string btnColor

    Text{
        text: btnName
        anchors.fill: parent
        font.pointSize: 17
        color: "white"
    }

    color: btnColor

}
