import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import "Controles"

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
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBSamples())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "FXs"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBFxs())
                }
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "ARRANGEMENTS"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBArrangements())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "INSTRUMENTS"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBInstruments())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "ROUTAGE"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBRoutages())
                }
            }
        }

        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "PROTOTYPES"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBPrototypes())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "SEQUENCES"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBSequences())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "MOTIFS"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getDBMotifs())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "FLOOREC"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "FLOOROUTE"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "GOOROUTE"
                zyva : Hlp.vide
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "GOOREC"
                zyva : Hlp.vide
            }
        }
    }
}
