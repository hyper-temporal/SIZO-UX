import QtQuick 2.0

Item {

    Column{
        TextInput{
            id : name
        }
        CtrlFiltreMIDI{
            id :filtre_source
        }
        CtrlRoutageMIDI{
            id:routage
        }
    }


}
