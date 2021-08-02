
import QtQuick 2.0
import "."

Item {
    height: 480
    width: 320
    LauncherList {
        id: ll
        anchors.fill: parent
        Component.onCompleted: {
            addExample(
                        "Configuration MIDI",
                        "plugSignal MIDI IO ",
                        Qt.resolvedUrl("Controles/CtrlConfigMIDI.qml"));
            addExample(
                        "Configuration Audio",
                        "selection des IO Audio",
                        Qt.resolvedUrl("Controles/CtrlConfigAudio.qml"));

        }
    }
}
