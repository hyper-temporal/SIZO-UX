import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Item{
    id: bouton
    anchors.fill: parent
    property string colFill: "darkBlue"
    property string colBord: "lightGray"
    property string colTexteUp: colBord
    property string colTexteDown: colFill
    property string letexte: ""
    property var zyva: Hlp.vide
    Button {
        id: control
        anchors.fill: parent
        contentItem: Text
        {
            text : letexte
            elide : Text.ElideMiddle
            verticalAlignment : Text.AlignVCenter
            horizontalAlignment : Text.AlignHCenter
            color: control.down?colTexteDown:colTexteUp
        }
        background: Rectangle{
            color: control.down?colBord:colFill
            border.color: control.down?colFill:colBord
        }
        onPressed: {
            if(zyva !== null ){ zyva()}
        }
    }

}
