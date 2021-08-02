import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "../../js/Helpers.js" as Hlp


Item {
    property int margin: 11
    width: mainLayout.implicitWidth + 2 * margin
    height: mainLayout.implicitHeight + 2 * margin

    property var entrees : OndeStore.getInputs_Audio()
    property var sorties : OndeStore.getOutputs_Audio()

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent
        anchors.margins: margin
        GroupBox {
            id: configGOO
            title: "Configuration Midi / GOO"
            Layout.fillWidth: true
            RowLayout {
                anchors.fill: parent
                ComboBox{
                    model : entrees
                }
            }
        }
        GroupBox {
            id: configFLOO
            title: "Configuration Audio / Goo"
            Layout.fillWidth: true
            RowLayout {
                anchors.fill: parent
                ComboBox{
                    model : sorties
                }
            }
        }
    }

}


