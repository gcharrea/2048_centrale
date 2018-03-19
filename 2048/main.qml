import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: window
    visible: true
    width: 640
    height: 480
    color: "#ffffff"


    Grid {
        id: rectangle
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

        Keys.onPressed:
        {
            switch (event.key)
            {
             case Qt.Key_Enter :
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
            Rectangle
            {
                border.color: "black"
                width: 100
                height: 100

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
