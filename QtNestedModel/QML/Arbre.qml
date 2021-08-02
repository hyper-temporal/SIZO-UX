import QtQuick 2.6
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.1
import Qt.labs.folderlistmodel 1.0
import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import DrTools 1.0

Item {
    id : root
    focus: true
    property bool hov: true
    property int highestZ: 0
    property double addx: 0.1
    property double addy: 0.1
    property double zoomx: 0.01
    property double zoomy: 0.01
    property bool ctrlpressed : false

    width: 600
    height: 600
    Keys.onPressed: {
        keyPressEvent(event)

    }
    Keys.onReleased: {
        keyReleasedEvent(event)
    }


    Rectangle{
        anchors.fill: parent
        Arbre
        {
            id:             graphe
            visible:        true
            anchors.fill:   parent
            c_fond:         "#fff"
            c_data_tour:    "#2af"
            c_centre:       "#afa"
            c_connection:   "#f77"
            fontsize:       12
            hoveredAccepted:        hov
            curseurDeplacement:     Qt.SizeAllCursor
            curseurGrabInput:       Qt.ClosedHandCursor
            curseurPlugOutput:      Qt.PointingHandCursor
            curseurVide:            Qt.CrossCursor
            Component.onCompleted: {

            }
        }
    }
    function  keyPressEvent(event)
    {
        switch (event.key)
        {
        case Qt.Key_Escape:
            break;
        case Qt.Key_Control:
            ctrlpressed = true
            break;
        case Qt.Key_Plus:
            graphe.zoom(zoomx)
            break;
        case Qt.Key_Minus:
            graphe.zoom(-zoomx)
            break;
        case Qt.Key_Left:
            graphe.addCentreX(-addx)
            break;
        case Qt.Key_Right:
            graphe.addCentreX(addx)
            break;
        case Qt.Key_Up:
            graphe.addCentreY(-addy)
            break;
        case Qt.Key_Down:
            graphe.addCentreY(addy)
            break;
        default:
            break;
        }
    }

    function  keyReleasedEvent(event)
    {
        switch (event.key)
        {
        case Qt.Key_Control:
            ctrlpressed = false
            break;
        default:
            break;
        }
    }
}
