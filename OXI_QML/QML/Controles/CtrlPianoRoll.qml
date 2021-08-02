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

    property bool hov: false

    property int highestZ: 0
    property double centrx: 0.0
    property double centry: 0.0
    property double addx: 0.001
    property double addy: 0.001
    property double zoomx: 0.01
    property double zoomy: 0.01
    property bool ctrlpressed : false

    Keys.onPressed: {
        keyPressEvent(event)
    }
    Keys.onReleased: {
        keyReleasedEvent(event)
    }
    Rectangle{
        anchors.fill: parent
        Gantt
        {
            id:             gantt
            visible:        false
            anchors.fill:   parent
            c_fond:         "#fff"
            c_data_tour:    "#2af"
            c_data:         "#afa"
            c_edited:       "#f77"
            c_hovered:      "pink"
            c_grid_base:    "#00f"
            c_grid_meta:    "#04f"
            c_grid_sub:     "#08f"

            hoveredAccepted:    hov
            secondeParPixel:    0.001
            pixperline:         64
            duree:              12
            curseurEdge:        Qt.SplitHCursor
            curseurMoveH:       Qt.SizeAllCursor
            curseurMoveV:       Qt.SizeVerCursor
            curseurBase:        Qt.CrossCursor
            Component.onCompleted: {
                gantt.visible=true
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
            if(ctrlpressed){
                gantt.pixperline += (gantt.pixperline * zoomy)
            }else{
                gantt.secondeParPixel -= ( gantt.secondeParPixel * zoomx)
            }
            break;
        case Qt.Key_Minus:
            if( ctrlpressed){
                gantt.pixperline -= (gantt.pixperline * zoomy)
            }else{
                gantt.secondeParPixel += (gantt.secondeParPixel * zoomx)
            }
            break;
        case Qt.Key_Left:
            gantt.addCentreX(-addx)
            break;
        case Qt.Key_Right:
            gantt.addCentreX(addx)
            break;
        case Qt.Key_Up:
            gantt.addCentreY(-addy)
            break;
        case Qt.Key_Down:
            gantt.addCentreY(addy)
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
