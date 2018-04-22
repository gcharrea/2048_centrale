import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import Qt.labs.calendar 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#ffffff"


    function setGameOver(){
        endGameDialog.open();
    }

    Connections {
        target: plateau
        onSignalGameOver: {
            setGameOver();
        }
    }

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

            Rectangle {
                id: rectangle
                implicitWidth: 100
                implicitHeight: 35
                border.color: "lightgrey"
                radius: 4

                ToolButton {
                    id: prevButton
                    background: Rectangle{
                        color: "#00000000"
                    }

                    text: "\u25C0"
                    anchors.verticalCenterOffset: -1
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                    onClicked: {
                        plateau.previous();
                        table_jeu.focus = true
                    }
                }

                Text {
                    id: coupText
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: plateau.stateQML[0];
                }

                ToolButton {
                    id: nextButton
                    background: Rectangle{
                        color: "#00000000"
                    }
                    text: "\u25B6"
                    anchors.verticalCenterOffset: 0
                    anchors.verticalCenter: prevButton.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 5
                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                    onClicked: {
                        plateau.next();
                        table_jeu.focus = true
                    }
                }

            }

            ToolButton
            {
                id : newButton
                text: "Nouvelle partie"
                focusPolicy: Qt.ClickFocus
                highlighted: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: Qt.application.font.pixelSize

                onClicked: {
                    plateau.newGame()
                    table_jeu.focus = true
                }

                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 35
                    border.color: "lightgrey"
                    radius: 4
                }

            }

            Text {
                id: scoreText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                text: plateau.stateQML[2];
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
        color : "darkgrey"

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


        Repeater
        {
            model : plateau.taille()
            Tuile
            {
                i: index%4
                j: (index - i)/4
                c: plateau.plateauQML[index*plateau.nbPara() + 1]
                cTexte: plateau.plateauQML[index*plateau.nbPara() + 2]
                texte: plateau.plateauQML[index*plateau.nbPara() + 0]
            }
        }

        Dialog {
            id: endGameDialog
            topPadding: 0
            visible: false

            Rectangle {
                id: rectangle1
                width: 400
                height: 290
                color: "#ffffff"
                border.width: 3
                border.color: "black"
                radius: 8
                anchors.verticalCenter: window.verticalCenter
                anchors.horizontalCenter: window.horizontalCenter

                ColumnLayout {
                    id: columnLayout
                    width: 100
                    height: 100
                    anchors.top: parent.top
                    anchors.topMargin: 22
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: gameOverText
                        text: "Game Over"
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        anchors.verticalCenterOffset: -49
                        anchors.horizontalCenterOffset: 1
                        color: "black"
                        anchors.centerIn: parent
                        font.pixelSize: Qt.application.font.pixelSize * 3
                    }

                    Text {
                        id: finalScoreText
                        text: plateau.stateQML[2]
                        horizontalAlignment: Text.AlignHCenter
                        anchors.centerIn: parent
                        font.pixelSize: 12
                    }

                    Text {
                        id: bestScoreText
                        text: plateau.stateQML[4]
                        font.pixelSize: 12
                    }

                    RowLayout {
                            id: rowLayout
                            width: 193
                            height: 60
                            anchors.horizontalCenter: parent.horizontalCenter

                            ColumnLayout {
                                width: 100
                                height: 100

                                Button {
                                    id: nextButtonName_1
                                    background: Rectangle{
                                        color: "#00000000"
                                    }
                                    text: "\u25B2"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {
                                        plateau.changeName(0,1);
                                    }
                                }

                                Text {
                                    id: nameText_1
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    font.pixelSize: Qt.application.font.pixelSize * 2
                                    font.bold: true
                                    text: plateau.stateQML[3][0];
                                }

                                Button {
                                    id: prevButtonName_1
                                    background: Rectangle{
                                        color: "#00000000"
                                    }

                                    text: "\u25BC"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {

                                        plateau.changeName(0,-1);
                                    }
                                }
                            }

                            ColumnLayout {
                                width: 100
                                height: 100

                                Button {
                                    id: nextButtonName_2
                                    background: Rectangle{
                                        color: "#00000000"
                                    }

                                    text: "\u25B2"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {
                                        plateau.changeName(1,1);
                                    }
                                }

                                Text {
                                    id: nameText_2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    font.pixelSize: Qt.application.font.pixelSize * 2
                                    font.bold: true
                                    text: plateau.stateQML[3][1];
                                }

                                Button {
                                    id: prevButtonName_2
                                    background: Rectangle{
                                        color: "#00000000"
                                    }

                                    text: "\u25BC"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {
                                        plateau.changeName(1,-1);
                                    }
                                }
                            }

                            ColumnLayout {
                                width: 100
                                height: 100

                                Button {
                                    id: nextButtonName_3
                                    background: Rectangle{
                                        color: "#00000000"
                                    }

                                    text: "\u25B2"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {
                                        plateau.changeName(2,1);
                                    }
                                }

                                Text {
                                    id: nameText_3
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    font.pixelSize: Qt.application.font.pixelSize * 2
                                    font.bold: true
                                    text: plateau.stateQML[3][2];
                                }

                                Button {
                                    id: prevButtonName_3
                                    background: Rectangle{
                                        color: "#00000000"
                                    }

                                    text: "\u25BC"
                                    font.pixelSize: Qt.application.font.pixelSize * 1.6
                                    onClicked: {
                                        plateau.changeName(2,-1);
                                    }
                                }
                            }
                        }


                    RowLayout {
                        width: 100
                        height: 100
                        anchors.horizontalCenter: parent.horizontalCenter

                        Button {
                            text: qsTr("Save Score")
                            onClicked:{
                                plateau.saveScore();
                            }
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

