import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    width: 620
    height: 450
    visible: true

    MouseArea {
        anchors.fill: parent
        onClicked: {
            Qt.quit();
        }
    }

    GridView {
        id: gridView1
        x: 77
        y: 113
        width: 247
        height: 34
        antialiasing: false
        transformOrigin: Item.Center
        flow: GridView.FlowTopToBottom
        cellWidth: 70
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        cellHeight: 64
        delegate: Item {
            x: 5
            height: 50

            Text {
                id: text1
                text: qsTr("Zadania")
                anchors.fill: parent
                font.pixelSize: 12
            }

            Text {
                id: text2
                x: 8
                y: 8
                text: qsTr("Procesory")
                font.pixelSize: 12
            }

            Text {
                id: text3
                x: 128
                y: 8
                text: qsTr("O programie")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 12
            }
        }
    }
}

