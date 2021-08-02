import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import DrTools 1.0

Item {
    id: vueJson
    TreeModel {
        id: jsonEditModel
    }
    JsonTreeView {
        id: viewEdit
        model: jsonEditModel
    }
//    ItemSelectionModel {
//        id: selEdit
//        model: jsonEditModel
//    }
    function setup(index){
        jsonEditModel.setModelRoot(
                    jsonModel.data(index),
                    jsonModel.objet(index)
                    )
    }
}
