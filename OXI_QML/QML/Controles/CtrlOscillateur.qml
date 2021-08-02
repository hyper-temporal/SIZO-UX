import QtQuick 2.0
import DrTools 1.0
import QtQuick.Controls 2.2
import "."
Item {
    Column{
        TextInput{
            id :name
        }

        ComboBox{
            id :type
            model: [
                "icek"          ,
                "ice"           ,
                "hype"          ,
                "env"           ,
                "gran"          ,
                "mixeur"        ,
                "aleatoire"     ,
                "repartiteur"   ,
                "shape"         ,
                "wavetable"     ,
                "eshape"        ,
            ]



        }

        CtrlCompound{
            id :formule
        }
        CtrlWaveTable{
            id: wavetable
        }

        CtrlShape{
            id:shape
        }


        ListView{
            id : events
            //model : store.getEvents()
        }

    }

}
