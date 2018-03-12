import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    color: "#aa0000"
    title: qsTr("Hello World")

    Rectangle {
        id: rectangle
        x: 281
        y: 201
        width: 78
        height: 78
        color: "#5500ff"

        Text {
            id: text1
            x: 0
            y: 0
            width: 78
            height: 78
            text: vueObjectCpt.pionQML
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.Fit
            font.pixelSize: 25
            focus: true
            Keys.onPressed:
                switch (event.key)
                {
                case Qt.Key_Up:
                    vueObjectCpt.increment();
                    break;

                case Qt.Key_Down:
                    vueObjectCpt.decrement();
                    break;
                }
        }
    }
}
