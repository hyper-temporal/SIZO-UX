import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."
import "./Controles"
import "../js/Helpers.js" as Hlp

Item {
    id : mainCtrl
    visible: true
    property int instruNum: 0
    property var instrumentdatas: null
    GridLayout
    {
        id : mainlayout
        anchors.fill: parent
        RowLayout{
            Layout.row: 1
            Layout.rowSpan: 1
            Layout.column: 1
            Layout.columnSpan: 6
            Layout.fillHeight: true
            Layout.fillWidth: true
            Rectangle{
                color: "green"
                Layout.fillHeight: true
                Layout.fillWidth: true
                ArbreEnvironnment{
                    id : arbre
                    anchors.fill: parent
                }
            }
            Rectangle{
                color: "#555"
                Layout.fillHeight: true
                Layout.fillWidth: true
                MenuConfig{
                    id : conf
                    anchors.fill: parent

                }
            }
            Rectangle{
                color: "#444"
                Layout.fillHeight: true
                Layout.fillWidth: true
                MenuDBs{
                    id : menuDBS
                    anchors.fill: parent
                }
            }
        }

        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row: 2
            Layout.rowSpan: 1
            Layout.column: 1
            Layout.columnSpan: 6
            CtrlShape{
                name:"test"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Component.onCompleted: {
//                    var t = OndeStore.test()
                }
            }
            Rectangle{
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
                    radius      : 3.0
                    Component.onCompleted: {
                        syncParams()
                        setValeur(0.5)
                    }
                }
            }
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
            Rectangle{
                color: "#111"
                Layout.fillHeight: true
                Layout.fillWidth: true
                DrXY
                {
                    id: xycross
                    antialiasing: true
                    anchors.fill: parent
                    fond        : "black"
                    light       : "white"
                    repere      : "red"
                    minX        : -1.0
                    maxX        : 2.0
                    minY        : -1.0
                    maxY        : 2.0
                    Component.onCompleted: {
                        syncParams()
                        setValeurs(0.5,0.5)
                    }
                }
            }
        }

        RowLayout{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.row: 3
            Layout.rowSpan: 2
            Layout.column: 1
            Layout.columnSpan: 6
            Rectangle{
                color: "red"
                Layout.fillHeight: true
                Layout.fillWidth: true
                Enveloppe
                {
                    id:enveloppeMaison
                    anchors.fill: parent
                    fond    :   "black"
                    bord     :  "#626262"
                    fondhaut :  "black"
                    fondBas  :  "black"
                    centre   :  "#ff0000"
                    courbe   :  "#ffffff"
                    points   :  "#00ff00"
                }
            }
            Rectangle{
                color: "#2d8"
                Layout.fillHeight: true
                Layout.fillWidth: true
                CtrlPianoRoll
                {
                    id: gantt
                    anchors.fill: parent
                    Component.onCompleted: {
                        gantt.forceActiveFocus()
                    }
                }
//                MouseArea{
//                    anchors.fill: parent
//                    onClicked: {
//                    }
//                }
            }
        }



//        RowLayout{
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//            Layout.row:6
//            Layout.rowSpan: 1
//            Layout.column: 1
//            Layout.columnSpan: 6
//            Rectangle{
//                color: "#222"
//                Layout.fillHeight: true
//                Layout.fillWidth: true
//                Enveloppe
//                {
//                    id:enveloppeAny
//                    anchors.fill: parent
//                    fond    :   "white"
//                    bord     :  "#626262"
//                    fondhaut :  "white"
//                    fondBas  :  "white"
//                    centre   :  "#ff0000"
//                    courbe   :  "lightblue"
//                    points   :  "#00ff00"
//                }
//            }
//            Rectangle{
//                color: "#333"
//                Layout.fillHeight: true
//                Layout.fillWidth: true
//                ScopeView {
//                    id: scopeView
//                    anchors.fill: parent
//                }
//            }
//        }
    }
    Component.onCompleted: {
    }
}
