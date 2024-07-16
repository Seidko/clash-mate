import QtQuick 6.6
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: page
    width: 480; height: 320
    color: "lightgray"

    ColumnLayout {
        Text {
            id: helloText
            text: "Hello world!"
            y: 30
            font.pointSize: 24; font.bold: true
        }
        RowLayout {
            Button {
                text: "Ok"
            }
            Button {
                text: "Cancel"
            }
        }
    }
}