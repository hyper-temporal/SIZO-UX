import QtQuick.Controls 1.5
import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import DrTools 1.0

TreeView {
    id: viewRoot
    selection: sel
    TableViewColumn {
        id : colonneNom
        title: ""
        role: "key"
        resizable: true
    }
    itemDelegate: Item {
        Text {
            anchors.fill: parent
            height: 70
            text: styleData.value   //plus salement documenté tu trouves pas
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                onClicked: {
                    modelIndex = styleData.index;
                    modelObjet =  viewRoot.model.data(modelIndex)
                    jsonMenu.open()
                }
            }
        }
    }
    onPressAndHold: {
        modelIndex = index
        modelObjet =  viewRoot.model.data(modelIndex)
        jsonMenu.open()
    }
    onClicked: {
        modelIndex = index
    }
    onDoubleClicked : {
        modelIndex = index
    }
}
