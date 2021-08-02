import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Item {
    property int margin: 11
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin

    Timer{
        running: true;
        repeat: false
        interval: 1000
        onTriggered: {
            gantt.hov=true
        }
    }

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: margin
        GroupBox {
            id: rowBox
            title: "Edition Séquence"
            Layout.fillWidth: true
            RowLayout {
                id: rowLayout
                anchors.fill: parent
                TextField {
                    placeholderText: "name pour identifier la séquence"
                    Layout.fillWidth: true
                }
                Button {
                    text: "save"
                }
            }
        }
        GroupBox {
            id: gridBox
            title: "Grid layout"
            Layout.fillWidth: true
            Layout.fillHeight: true
            CtrlPianoRoll
            {
                id: gantt
                anchors.fill: parent
                hov: false

                Component.onCompleted: {
                    gantt.forceActiveFocus()
                }
            }
        }
    }

}



