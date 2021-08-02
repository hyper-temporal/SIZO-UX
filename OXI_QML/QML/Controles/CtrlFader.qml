import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Rectangle{
    color: "#111"
    Layout.fillHeight: true
    Layout.fillWidth: true
    DrFader
    {
        id: fader
        antialiasing: true
        anchors.fill: parent
        fond        : "black"
        light       : "white"
        repere      : "red"
        min         : -1.0
        max         : 2.0
        horiz       : false
        Component.onCompleted: {
            syncParams()
            setValeur(0.5)
        }
    }
}

