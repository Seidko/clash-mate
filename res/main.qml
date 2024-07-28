import QtQuick 6.6
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

RowLayout {
    SystemPalette { id: cmPalette; colorGroup: SystemPalette.Active }

    id: root
    spacing: 0
    Layout.fillHeight: true
    Layout.fillWidth: true

    ColumnLayout {
        Layout.fillHeight: true
        Layout.maximumWidth: 160
        Layout.alignment: Qt.AlignTop
        
        spacing: 5

        Text {
            text: "Clash Mate"
            font.pixelSize: 25
            color: palette.text
            Layout.alignment: Qt.AlignHCenter
        }

        ToolButton {
            Layout.fillWidth: true
            icon.name: "office-chart-area"
            text: "DashBoard"
        }

        ToolButton {
            Layout.fillWidth: true
            icon.name: "applications-internet"
            text: "Proxies"
        }
    }

    ColumnLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true

        Rectangle {
            color: "grey"
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
