import QtQuick.Controls 1.5
import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Item {
    visible: true
    anchors.fill: parent

    property var modelIndex: null
    property var modelObjet: null

    JsonDialog {
        id: jsonDialog
        onFinirEdition: {
            if (modelIndex === null)
                jsonModel.append(modelObjet)
            else
                jsonModel.set(modelIndex, modelObjet)
        }
    }
    TreeModel {
        id: jsonModel
        Component.onCompleted: {
            var session = OndeStore.getSession()
            setModel(session)
//            setDefaultRoot()
        }
    }

    ItemSelectionModel {
        id: sel
        model: jsonModel
    }

    JsonMenu{
        id:jsonMenu

    }
    JsonTreeView {
        id: viewRoot
        model : jsonModel
        anchors.fill: parent
        Keys.onEscapePressed: {
            gantt.forceActiveFocus()
        }
    }

}
