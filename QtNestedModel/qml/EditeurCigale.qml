import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import "./Controles"

Item
{

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
