import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Rectangle
{
    color: "#111"
    Layout.fillHeight: true
    Layout.fillWidth: true
    DrPotard
    {
        id: potard
        antialiasing: true
        anchors.fill: parent
        fond        : "black"
        toursel     : "black"
        light       : "white"
        centre      : .5
        sens        : true
        cx          : .5
        cy          : .5
        deadz       : .25
        radius      : 3.
        Component.onCompleted: {
            syncParams()
            setValeur(0.5)
        }
    }
}

