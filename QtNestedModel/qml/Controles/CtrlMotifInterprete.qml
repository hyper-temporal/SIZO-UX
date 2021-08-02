import QtQuick 2.0
import DrTools 1.0
import QtQuick.Controls 2.2
import "."

Item {
    Column{
        Row{
            Text{
                text:"type"
            }
            ComboBox{
                id :type
                model: OndeStore.getAllMotifNames()
            }
            Button{
                text: "edit"
            }
        }
        Text{
            text:"pressions"
        }
        ComboBox{
            id : pressions
            model: OndeStore.getNbPressions()
        }
        Text{
            text:"Signature Rythmique"
        }
        Row {
            Text{
                text:"diviseur"
            }
            ComboBox{
                id : diviseur
                model: OndeStore.getMIDIValues()
            }
            Text{
                text:"multiplieur"
            }
            ComboBox{
                id : multiplieur
                model: OndeStore.getMIDIValues()
            }
        }
        Text{
            text:"resync"
        }
        CheckBox{
            id:resync
        }
    }

    //possible pour edition locale, et deconnectée (pb interruption?)
    //    function getAllMotifNames(){
    //        var list =  new Array()
    //        for(var key in master.session.DB_sequences.seqs){
    //            var el = master.session.DB_sequences.seqs[key]
    //            console.log(el.name)
    //            list.push(el.name)
    //        }
    //        return list
    //    }
}
