import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#ffffff"
    title: qsTr("Hello World")

    Grid {
        id: grid
        x: 144
        y: 40
        width: 400
        height: 400
        rows: 4
        columns: 4
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
