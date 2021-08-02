import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import "../js/Helpers.js" as Hlp
import "./Controles"

Item {
    function f(){
        return potard.value2Coord(0.5)
    }

    ColumnLayout
    {
        id: gridMain
        anchors.fill: parent
        spacing: 0
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "GOO config"
                zyva : function (){
                    Hlp.exposerObjet(OndeStore.getConfigGOO())
                }
            }
        }
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            CtrlBouton{
                letexte: "FLOO config"
                zyva : function (){
                  Hlp.exposerObjet(OndeStore.getConfigFLOO())
//                    console.log(OndeStore.getSortieAudio())
                }
            }
        }
    }
}
