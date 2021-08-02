import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls 1.5
import QtQml.Models 2.2
import DrTools 1.0


Dialog {
    id: dialogJson
    signal finirEdition(var o)
    function createJson() {
        dialogJson.title = qsTr("Add " + formJson.onom);
        dialogJson.open();
    }
    function editJson(index) {
        formJson.setup(index)
        dialogJson.title = qsTr("Edit " + formJson.onom);
        dialogJson.open();
    }

    focus: true
    modal: true
    title: qsTr("____")
    contentItem:
        JsonForm {
            id: formJson
        }
    standardButtons:
        Dialog.Ok | Dialog.cancel

    onAccepted: finirEdition(oedit)
}
