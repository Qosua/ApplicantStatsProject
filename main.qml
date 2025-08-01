import QtQuick 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Window {
    property color blackTheme1: "#1f1f1f";
    property color blackTheme2: "#262626";
    property color blackTheme3: "#404040";

    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")
    visibility: "Maximized";
    color: blackTheme3

    RightBar {

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: parent.width / 4

        ColumnLayout {

            CustomButton {

                btnName: "Математический факультет"
                height: 80
                btnColor: "green"

            }

        }
    }
}
