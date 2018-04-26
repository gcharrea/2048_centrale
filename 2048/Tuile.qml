//Tuile.qml
import QtQuick 2.9

Rectangle {
    width: 100
    height: 100
    color: "#00000000"

    property int i: 0
    property int j: 0
    property string c: "lightgrey"
    property string cTexte: "black"
    property string texte: ""

    x: i*100
    y: j*100

    Rectangle
    {
        width: 90
        height: 90
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        color: c

        Text
        {
            text: texte
            color: cTexte

            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.topMargin: 5
            anchors.fill: parent

            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Tahoma"
            minimumPixelSize: 20
            font.pixelSize: 40
            fontSizeMode: Text.HorizontalFit
        }
    }
}
