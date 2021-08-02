import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import "./Controles"


ListView {
    width: 100; height: 100
    model: myModel
    delegate: Rectangle {
        height: 25
        width: 100
        Text { text: modelData }
    }


    ColumnLayout
    {
        id: gridMain
        anchors.fill: parent
//        spacing: 0
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "SAMPLES"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "FXs"
                zyva : Hlp.vide
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "ARRANGEMENTS"
                zyva : Hlp.vide
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "PROTOTYPES"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "SEQUENCES"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "MOTIFS"
                zyva : Hlp.vide
            }
        }

    }
}
