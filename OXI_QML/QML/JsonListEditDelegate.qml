import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

ItemDelegate {
    id: jleDelegate
    checkable: true
    contentItem: ColumnLayout {
        spacing: 10
        Label {
            text: fullName
            font.bold: true
            elide: Text.ElideRight
            Layout.fillWidth: true
        }
        GridLayout {
            id: grid
            visible: false

            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            RoundButton {
                text: qsTr("+")
                highlighted: true
                anchors.margins: 20
                onClicked: {
                    currentContact = index
                    var c = contactView.model.get(index);
                    contactDialog.editContact(c)
                }
            }
            RoundButton {
                text: qsTr("~")
                highlighted: true
                anchors.margins: 20
                onClicked: {
                    currentContact = index
                    var c = contactView.model.get(index);
                    contactDialog.editContact(c)
                }
            }
            RoundButton {
                text: qsTr("-")
                highlighted: true
                anchors.margins: 20
                onClicked: {
                    contactView.model.remove(index)
                }
            }
        }
    }

    states: [
        State {
            name: "expanded"
            when: jleDelegate.checked

            PropertyChanges {
                target: grid
                visible: true
            }
        }
    ]
}
