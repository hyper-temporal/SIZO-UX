import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Rectangle{
    id: conteneur
    property string name: ""
    property int shapenum: -1
    property var dto: null
    Column{
        anchors.fill: parent
        Rectangle{
            color: "white"
            Layout.alignment: Qt.AlignCenter
            height: 20
            width: parent.width
            TextInput{
                text: name
                anchors.fill: parent
            }
        }
        Rectangle{
            color: "black"
            Layout.alignment: Qt.AlignCenter
            y:20
            width : parent.width
            height : parent.height - 20
            DrOnde
            {
                id: line
                antialiasing: true
                anchors.fill: parent
                fond    :   "black"
                bord     :  "#626262"
                fondhaut :  "black"
                fondBas  :  "black"
                centre   :  "#ff0000"
                courbe   :  "#ffffff"
                points   :  "#00ff00"
                interpoltype: 1
                looped  : false

            }
        }
    }
}

