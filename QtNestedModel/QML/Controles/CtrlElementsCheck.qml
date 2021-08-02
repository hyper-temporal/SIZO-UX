import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "../../js/Helpers.js" as Hlp

Item {
    id: rowBox
    property Component del : null
    property int margin: 20
    property var entrees : null
    property var valider : null
    property var selected : []
    property var modelIndex :null
    anchors.fill: parent
    ColumnLayout{
        anchors.fill: parent
        spacing: 20
        RowLayout {
            anchors.margins: 2*margin
            anchors.fill: parent
            ListView {
                id: midiInputs
                anchors.fill: parent
                model:  entrees
                delegate: Row {
                    width: midiInputs.width
                    height: 50
                    spacing: 5
                    CheckBox{
                        id :chk
                        checked:  false
                        text: nick
                        onCheckedChanged: {
                            midiInputs.model.etatIO(index,chk.checked)
                            console.log(index)
                        }
                        onPressAndHold: {
                            console.log(index)
                            chk.visible = false
                            editable.visible = true
                        }
                    }
                    TextField{
                        id : editable
                        hoverEnabled: true
                        visible: false
                        text: nick
                        onAccepted: {
                            midiInputs.model.changerAlias(index,editable.text)
                            editable.visible = false
                            chk.visible = true
                        }
//                        MouseArea{
//                            anchors.fill: parent
//                            onExited: {
//                                editable.visible = false
//                                chk.visible = true
//                            }
//                            onClicked: {mouse.accepted = false}

//                        }

                    }

                }
            }

        }
//        Button{
//            id : valid
//            Layout.alignment: Qt.AlignHCenter
//            onClicked: {
//                valider()
//                //                if(selected !== null && validata !== null)
//                //                    validata(selected)
//            }
//        }

    }

}




