import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Rectangle {

    Rectangle {
        id: buttonsBar
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left

        height: 36
        color: "transparent"

        property bool sortFlag: false

        RowLayout {
            anchors.fill: parent
            anchors.margins: 4
            anchors.leftMargin: 6
            anchors.rightMargin: 6
            spacing: 5

            Item {
                Layout.fillWidth: true
            }
            PageButton {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height

                btnIconSource: "qrc:/resources/icons/folder.png"
                btnIconColor: "#aeaeae"
                btnToolTipName: " Открыть папку хранения таблиц "
                btnToolTipDelay: 700

                onClicked: {
                    qmlHelper.openAppDataFolder();
                }

            }
            PageButton {

                property bool sortFlag: true

                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height

                btnIconSource: "qrc:/resources/icons/sort-alpha-down.png"
                btnIconColor: "#aeaeae"
                btnToolTipName: " Сортировать по имени "
                btnToolTipDelay: 700

                onClicked: {
                    if (sortFlag) {
                        sortFilterProxyModel.sort(0, Qt.DescendingOrder)
                        sortFlag = false
                    } else {
                        sortFilterProxyModel.sort(0, Qt.AscendingOrder)
                        sortFlag = true
                    }
                }

            }

        }
    }

    Rectangle {
        id: someKindOfBorder
        anchors.top: buttonsBar.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        color: "#2e2e2e"
        height: 1
    }

    Rectangle {
        id: viewRect
        anchors.top: someKindOfBorder.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: 10
        color: "transparent"

        ListView {

            model: sortFilterProxyModel
            spacing: 2
            clip: true

            anchors.fill: parent
            anchors.margins: 4

            delegate: Rectangle {
                width: viewRect.width - 10
                height: 30
                radius: 8

                color: {
                    if (!delegatHover.hovered)
                        return "#2c2e32"
                    else
                        return "#3f4247"
                }
                Behavior on color {
                    ColorAnimation {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        qmlHelper.sendSignalToProceedTable(tableName)
                    }
                }
                HoverHandler {
                    id: delegatHover
                    cursorShape: Qt.PointingHandCursor
                }
                Image {
                    id: icon
                    source: tableIconPath
                    height: parent.height - 10
                    width: parent.height - 10
                    //fillMode: Image.PreserveAspectFit
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 6
                }
                Text {
                    id: tableLastChangeDateText
                    text: "(" + tableLastChangeDate + ")"
                    font.pointSize: 9
                    color: "#999999"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon.right
                    anchors.margins: 4
                }
                Text {
                    id: tableNameText
                    text: tableName
                    font.pointSize: 10
                    color: "#eeeeee"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: tableLastChangeDateText.right
                    anchors.leftMargin: 4
                }

            }
        }
    }
}