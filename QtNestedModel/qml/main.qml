import QtQuick 2.0
import "../js/Helpers.js" as Hlp

Item {
    id : master
    height: 800
    width: 600
    property var session:null
    LauncherList {
        id: ll
        animTime : 100
        anchors.fill: parent
        Component.onCompleted: {
            session = OndeStore.getSession()
            addExample(
                        "Configuration",
                        "Connection IO MIDI-Audio, Session",
                        Qt.resolvedUrl("Configuration.qml"));
            addExample(
                        "Motifs",
                        "Gestion des Motifs",
                        Qt.resolvedUrl("Controles/CtrlMotifInterprete.qml"));
            addExample(
                        "Sequences",
                        "Gestion des Sequences",
                        Qt.resolvedUrl("Controles/CtrlSequence.qml"));
            addExample(
                        "Prototypes",
                        "Gestion des Prototypes",
                        Qt.resolvedUrl("Controles/CtrlGraph.qml"));
            addExample(
                        "Instruments",
                        "Gestion des Instruments",
                        Qt.resolvedUrl("Composer.qml"));
            addExample(
                        "FXs",
                        "Gestion des multi effets",
                        Qt.resolvedUrl("Controles/CtrlFXs.qml"));
            addExample(
                        "Impact synths",
                        "Gestion des preset synthese percussive",
                        Qt.resolvedUrl("Controles/CtrlPercussive.qml"));
        }
    }
}
