import QtQuick 6.6
import QtQuick.Controls
import QtQuick.Layouts
import 

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
            on
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