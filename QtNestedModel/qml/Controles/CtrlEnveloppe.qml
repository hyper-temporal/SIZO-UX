import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Item {

    Column{
        Text{
            text :"name"
        }
        TextInput{
            id:name
        }
        Text{
            text :"type"
        }
        ComboBox{
            id :type
            visible: true
            model: [
                "adr"  ,
                "adsr" ,
                "gadr" ,
                "gadsr",
                "any"  ,
                "gany" ,
            ]
        }
        Text{
            text :"enveloppe"
        }
        Rectangle{
            color: "red"
            width: 200
            height: 100
            Enveloppe
            {
                id:enveloppeMaison
                anchors.fill: parent
                fond    :   "black"
                bord     :  "#626262"
                fondhaut :  "black"
                fondBas  :  "black"
                centre   :  "#ff0000"
                courbe   :  "#ffffff"
                points   :  "#00ff00"
            }
        }
        Text{
            text :"evenments"
        }
        CtrlEnveloppe{
            id : events
        }
    }
}
