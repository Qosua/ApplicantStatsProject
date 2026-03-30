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

    // pages menu
    Rectangle {
        id: pagesMenu
        width: 48
        radius: 12

        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 8
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        border.color: "#434343"
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
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: pagesMenu.right

        anchors.margins: 8
        anchors.topMargin: 10
        anchors.bottomMargin: 10

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
}



