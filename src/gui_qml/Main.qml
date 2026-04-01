import QtQuick
import QtQuick.Layouts
import QtGraphs
import QtQuick.Controls
import ApplicantStatsProjectModule

Window {
    id: window

    property int currentPageIndex: 0

    width: 1280; minimumWidth: 320
    height: 720; minimumHeight: 200

    visible: true
    color: "#26282b"
    title: ""

    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.clearRect(0, 0, parent.width, parent.height)
            var cx = width * 0.1
            var cy = -height * 0.05
            var grad = ctx.createRadialGradient(cx, cy, 0, cx, cy, width * 0.20)
            grad.addColorStop(0.0, "rgba(85, 109, 163, 0.5)")
            grad.addColorStop(1.0, "rgba(85, 109, 163, 0.0)")
            ctx.fillStyle = grad
            ctx.fillRect(0, 0, width, height)
        }
    }

    // pages menu
    Rectangle {
        id: pagesMenu
        width: 48
        radius: 12

        anchors.top: parent.top
        anchors.bottom: statusBar.top
        anchors.left: parent.left
        anchors.margins: 10
        anchors.topMargin: 10
        anchors.bottomMargin: 0

        border.color: "#323232"
        border.width: 1

        color: "#191a1c"

        ColumnLayout {

            property int innerPadding: 6

            spacing: 8

            anchors.fill: parent
            anchors.topMargin: innerPadding

            PageButton {
                Layout.preferredWidth: parent.width - (parent.innerPadding * 2)
                Layout.preferredHeight: parent.width - (parent.innerPadding * 2)
                Layout.alignment: Qt.AlignHCenter

                btnIconSource: "qrc:/resources/icons/stats.png"
                btnToolTipName: " Статистика "

                isBtnChecked: (window.currentPageIndex === 0)
                onClicked: {
                    window.currentPageIndex = 0
                }

            }
            PageButton {
                Layout.preferredWidth: parent.width - (parent.innerPadding * 2)
                Layout.preferredHeight: parent.width - (parent.innerPadding * 2)
                Layout.alignment: Qt.AlignHCenter

                btnIconSource: "qrc:/resources/icons/menu-burger.png"
                btnToolTipName: " Логи "

                isBtnChecked: (window.currentPageIndex === 1)
                onClicked: {
                    window.currentPageIndex = 1
                }

            }
            PageButton {
                Layout.preferredWidth: parent.width - (parent.innerPadding * 2)
                Layout.preferredHeight: parent.width - (parent.innerPadding * 2)
                Layout.alignment: Qt.AlignHCenter

                btnIconSource: "qrc:/resources/icons/settings.png"
                btnToolTipName: " Настройки "

                isBtnChecked: (window.currentPageIndex === 2)
                onClicked: {
                    window.currentPageIndex = 2
                }

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
        anchors.bottom: statusBar.top
        anchors.right: parent.right
        anchors.left: pagesMenu.right

        anchors.margins: 8
        anchors.topMargin: 10
        anchors.bottomMargin: 0

        currentIndex: window.currentPageIndex

        StatsPage {
            id: splitView
        }

        Rectangle {
            color: "red"
        }

        Rectangle {
            color: "blue"
        }
    }

    // status bar
    Rectangle {
        id: statusBar

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 15
        anchors.rightMargin: 15
        anchors.topMargin: 5

        color: "#26282b"
        height: 30

        Text {
            text: "Путь:  C: > some > very > long > path > to > data > table.xlsx"
            font.pointSize: 11
            color: "#888888"

            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.top: parent.top
            anchors.horizontalCenter: parent.left
            anchors.verticalCenter: parent.verticalCenter

        }

    }

}



