import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#ffffff"

    header: ToolBar {
        contentHeight: toolButton.implicitHeight
        RowLayout {

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

            ToolButton {
                id: prevButton
                text: "\u25C0"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    // TODO
                }
            }

            Text {
                id: coupText
                text: plateau.stateQML[0];
            }

            ToolButton {
                id: nextButton
                text: "\u25B6"
                font.pixelSize: Qt.application.font.pixelSize * 1.6
                onClicked: {
                    // TODO
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

            ItemDelegate {
                text: qsTr("Charger partie")
                width: parent.width
                onClicked: {
                    fileDialog.open()
                    drawer.close()
                }
            }

            ItemDelegate {
                text: qsTr("Sauver partie")
                width: parent.width
                onClicked: {
                    saveDialog.open()
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

    Rectangle
    {
        id: table_jeu
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        objectName: "table_jeu"

        width: 100 * plateau.lignes()
        height: 100 * plateau.colonnes()
        radius: 10
        color : "grey"

        focus : true

        Keys.onPressed:
        {
            switch (event.key)
            {
            case Qt.Key_L :
                fileDialog.open();
                break;

            case Qt.Key_S :
                saveDialog.open();
                break;

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

        Grid {
            anchors.fill: parent

            rows : plateau.lignes()
            columns: plateau.colonnes()

            Repeater
            {
                model : plateau.taille()
                Rectangle
                {
                    width: 100
                    height: 100
                    color: "#00000000"

                    Rectangle
                    {
                        width: 90
                        height: 90
                        radius: 10
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter

                        color : plateau.colorQML[index]

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
        }

        FileDialog {
            id: fileDialog
            title: "Select a save"
            nameFilters: ["2048 game (*.2k8)", "all (*.*)"];
            folder: shortcuts.home
            onAccepted: {
                console.log("You chose: " + fileDialog.fileUrls)
                plateau.load(fileDialog.fileUrls);
                fileDialog.close();
            }
            onRejected: {
                console.log("Canceled")
                fileDialog.close();
            }
        }

        FileDialog {
            id: saveDialog
            title: "Select a save"
            nameFilters: ["2048 game (*.2k8)", "all (*.*)"];
            folder: shortcuts.home
            selectExisting: false
            onAccepted: {
                console.log("You chose: " + saveDialog.fileUrls)
                plateau.save(saveDialog.fileUrls);
                saveDialog.close();
            }
            onRejected: {
                console.log("Canceled")
                saveDialog.close();
            }
        }
    }

}


