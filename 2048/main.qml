import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#ffffff"

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.2
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Nouvelle partie")
                width: parent.width
                onClicked: {
                    plateau.newGame()
                    drawer.close()
                }
            }
        }
        onClosed: table_jeu.focus = true
    }

    StackView {
        id: stackView
        anchors.fill: parent
    }




    // Partie table de jeu

    Grid {
        id: table_jeu
        x: 8
        y: 75
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        objectName: "table_jeu"
        rows : plateau.lignes()
        columns: plateau.colonnes()

        width: 100 * plateau.lignes()
        height: 100 * plateau.colonnes()

        focus : true

        Repeater
        {
            model : plateau.taille()
            Rectangle
            {
                width: 100
                height: 100

                Rectangle
                {
                    border.color: "black"
                    width: 90
                    height: 90
                    radius: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter

                    Text
                    {
                        text : plateau.plateauQML[index]
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 25
                    }
                }
            }
        }

        Keys.onPressed:
        {
            switch (event.key)
            {
            case Qt.Key_N :
                plateau.newGame();
                break;

            case Qt.Key_Left:
                plateau.gauche();
                break;

            case Qt.Key_Right:
                plateau.droite();
                break;

            case Qt.Key_Down:
                plateau.bas();
                break;

            case Qt.Key_Up:
                plateau.haut();
                break;
            }
        }
    }
}
