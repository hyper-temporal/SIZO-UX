import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import "."

Item {

    property int wtnum : -1
    Text{
       text:"WaveTable Editor"
    }
    TextInput{
        id:name
    }
    ColumnLayout{
        CtrlShape{
            id: wave
        }
    }

}
