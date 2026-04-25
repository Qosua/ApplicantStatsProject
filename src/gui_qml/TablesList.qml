import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Rectangle {

    id: tablesList
    property bool collapsed: false
    readonly property int collapsedHeight: buttonsBar.height + 1

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
            anchors.margins: 3
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            spacing: 7

            PageButton {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height

                btnIconSource: "qrc:/resources/icons/angle-down.png"
                btnIconColor: "#aeaeae"
                btnToolTipName: tablesList.collapsed ? " Развернуть " : " Свернуть "
                btnToolTipDelay: 700

                rotation: tablesList.collapsed ? 180 : 0
                Behavior on rotation {
                    NumberAnimation {
                        duration: 150; easing.type: Easing.OutQuad
                    }
                }

                onClicked: {
                    tablesList.collapsed = !tablesList.collapsed
                }

            }
            Item {
                Layout.fillWidth: true
            }
            PageButton {
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: parent.height

                btnIconSource: "qrc:/resources/icons/plus.png"
                btnIconColor: "#aeaeae"
                btnToolTipName: " Добавить таблицу "
                btnToolTipDelay: 700

                onClicked: {
                    qmlHelper.openDownloadsFolder();
                }

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
        visible: !tablesList.collapsed
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
        visible: !tablesList.collapsed
        anchors.top: someKindOfBorder.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.margins: 10
        color: "transparent"

        ListView {

            id: listView
            model: sortFilterProxyModel
            spacing: 2
            clip: true

            anchors.fill: parent
            anchors.margins: 4

            delegate: Rectangle {

                readonly property bool selected: qmlHelper.currentTablePath === tableFullPath

                width: viewRect.width - 10
                height: 30
                radius: 8

                color: {
                    if (selected)
                        return "#3a4660"
                    if (delegatHover.hovered)
                        return "#3f4247"
                    return "#2c2e32"
                }
                Behavior on color {
                    ColorAnimation {
                        duration: 100
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        qmlHelper.currentTablePath = tableFullPath
                        qmlHelper.sendSignalToProceedTable(tableName)
                    }
                }
                HoverHandler {
                    id: delegatHover
                    cursorShape: Qt.PointingHandCursor
                }
                Text {
                    id: tableLastChangeDateText
                    text: "(" + tableLastChangeDate + ")"
                    font.pointSize: 9
                    color: "#999999"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.margins: 4
                }
                Image {
                    id: icon
                    source: tableIconPath
                    height: parent.height - 10
                    width: parent.height - 10
                    //fillMode: Image.PreserveAspectFit
                    anchors.left: tableLastChangeDateText.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 6
                }
                Text {
                    id: tableNameText
                    text: tableName
                    font.pointSize: 10
                    color: "#eeeeee"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: icon.right
                    anchors.leftMargin: 4
                }

            }
        }
    }
}