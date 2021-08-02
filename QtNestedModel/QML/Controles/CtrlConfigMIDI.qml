import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "../../js/Helpers.js" as Hlp


ColumnLayout {
    id: mainLayout
    property int margin: 50
    anchors.margins: margin
    GroupBox {
        id:gb1
        title: "MIDI INPUTS"
        implicitWidth: parent.width
        implicitHeight: (parent.height-valid.height)/2
        CtrlElementsCheck{
            id : midiIns
            entrees : mdlMidiIns
//            valider: OndeStore.syncEtatIO
        }
    }
    GroupBox {
        id:gb2
        title: "MIDI OUTPUTS"
        implicitWidth: parent.width
        implicitHeight: parent.height-gb1.height-valid.height
        CtrlElementsCheck{
            id: midiOuts
            entrees : mdlMidiOuts
//            valider: OndeStore.syncEtatIO
        }
    }
    Button{
        id : valid
//        implicitWidth: parent.width
        width: 150
        height: 50
        Layout.alignment: Qt.AlignHCenter
        onClicked: {
            OndeStore.syncEtatIO()
        }
    }
}



