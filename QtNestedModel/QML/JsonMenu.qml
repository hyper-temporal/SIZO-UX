import QtQuick.Controls 1.5
import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import DrTools 1.0


Menu {
    id: jsonMenu

    ColumnLayout{
        Label {
            padding: 10
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment  : Qt.AlignVCenter
            text:  modelObjet?modelObjet:""
            font.bold: true
        }
        MenuItem {
            text: qsTr("Edit")
            onTriggered: {
                jsonDialog.editJson(modelIndex)
                close()
            }
        }
    }
}

