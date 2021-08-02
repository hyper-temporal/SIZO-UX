import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtPositioning 5.0
import QtDataVisualization 1.0
import QtQml.Models 2.3
import QtQuick 2.0
import QtCharts 2.0

Item {
    id : principal
    property int currentIndex: -1
    property bool zoomaction: false
    property bool m_istouching: false

    DomaineDef{
        id: dd
        xmin: 0.0
        xmax: 1.0
        ymin: -1.0
        ymax: 1.0
    }
    property  var point : null
    property   int cn   :  -1
    property   int cr   :  2

    ChartView {
        id: chartView
        anchors.fill: parent
        //                plotArea: Qt.rect(0,0,width,height)
        //                title.visible: false
        animationOptions: ChartView.NoAnimation
        antialiasing: true
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onPressed: {
                if(zoomaction){
                    if (m_istouching)
                        return;
                    return;
                }else{
                    var np = point2Value(mouse)
                    startEdit(np);
                }
                mouse.accepted = true
            }
            onMouseXChanged: {
                var np = point2Value(mouse)
                movePoint(np)
            }
            onMouseYChanged: {
                var np = point2Value(mouse)
                movePoint(np)
            }
            onReleased: {
                console.log("Released MouseArea")
                console.log(point2Value(mouse))
            }
            onDoubleClicked: {
                var np = point2Value(mouse)
                ajouterPoint(np)
            }
            Rectangle{
                id: zoomRect
                color: "#AAAAAA"
                opacity: 0.4
                visible: false
            }
        }
        ValueAxis {
            id: xAxis
            min: dd.xmin
            max: dd.xmax
            labelsVisible: false
            gridVisible: false
            lineVisible: false
            titleVisible: false
            minorGridVisible: false
        }
        ValueAxis {
            id: yAxis
            min: dd.ymin
            max: dd.ymax
            labelsVisible: false
            gridVisible: false
            lineVisible: false
            titleVisible: false
            minorGridVisible: false
        }
        LineSeries{
            id: editionPoints2D
            XYPoint{ x: 0.0 ; y: 0.0 }
            XYPoint{ x: 1.0 ; y: 0.0 }
            axisX: xAxis
            axisY: yAxis
        }
        ScatterSeries{
            id:selectedPoints
            axisX: xAxis
            axisY: yAxis
        }
    }

    Keys.onPressed:{
        keyPressEvent(event)
    }
    Keys.onReleased:{
        keyPressEvent(event)
    }

    function movePoint(np){
        console.log( np.y )
        console.log(dd.ymax)

        if(currentIndex >0 && currentIndex<editionPoints2D.count-1 )
        {
            var pav = editionPoints2D.at(currentIndex-1);
            var pap = editionPoints2D.at(currentIndex+1);
            if( np.x<pav.x){
                np.x=pav.x
            }
            if( np.x>pap.x){
                np.x=pap.x
            }
            if( np.y<dd.ymin){
                np.y=dd.ymin
            }
            if( np.y>dd.ymax){
                np.y=dd.ymax
            }
            editionPoints2D.replace(currentIndex,np.x,np.y);
            selectedPoints.replace(0,np.x,np.y);
            //            modifierPoint(currentIndex,np.x,np.y)
        }
    }

    function startEdit(np){
        currentIndex = pointProcheX(np)
        selectedPoints.clear()
        var lp =editionPoints2D.at(currentIndex)
        selectedPoints.append(lp.x,lp.y)
    }
    function stopEdit(){
        currentIndex = -1;
        selectedPoints.clear();
    }

    function keyReleaseEvent(event)
    {
        switch (event.key)
        {
        case Qt.Key_Control:
            zoomaction = false
            break;
        default:
            break;
        }
    }

    function  keyPressEvent(event)
    {
        console.log(event)
        switch (event.key)
        {
        case Qt.Key_Escape:
            chartView.zoomReset();
            break;
        case Qt.Key_Control:
            _zoomaction = true;
            break;
        case Qt.Key_Plus:
            chartView.zoomIn();
            break;
        case Qt.Key_Minus:
            chartView.zoomOut();
            break;
            //![1]
        case Qt.Key_Left:
            chartView.scrollLeft(10);
            break;
        case Qt.Key_Right:
            chartView.scrollRight(10);
            break;
        case Qt.Key_Up:
            chartView.scrollUp(10);
            break;
        case Qt.Key_Down:
            chartView.scrollDown(10);
            break;
        default:
            break;
        }
    }
    function ajouterPoint(np){
        currentIndex = pointApresX(np)
        editionPoints2D.insert(currentIndex+1,np.x,np.y)
        //        insertPoint(currentIndex+1,np.x,np.y)
        currentIndex +=1
        selectedPoints.clear()
        selectedPoints.append(np.x,np.y)
    }

    function pointApresX(point)
    {
        var serie = editionPoints2D;
        for (var inx =-1 ;inx<serie.count-1;inx++) {
            if(
                    point.x === serie.at(inx).x
                    || point.x < serie.at(inx+1).x
                    ){
                console.info( "PointApresX " , inx)
                return inx;
            }
        }
        console.info( "nope " )
        return -1;
    }
    function pointProcheX(point)
    {
        var serie = editionPoints2D;
        var papx = pointApresX(point);
        if(papx >= 0 && papx<serie.count-1){
            var distav = Math.abs(serie.at(papx).x-point.x);
            var distap = Math.abs(serie.at(papx+1).x-point.x);
            papx =  distav<=distap?papx:papx+1;
        }
        console.info( "PointApresX " , papx)
        return papx;
    }

    function point2Value(m){
        var p =Qt.point(m.x,m.y)
        return chartView.mapToValue(p,editionPoints2D)
    }

    function changerSeries(element){
        chartView.removeAllSeries()
        chartView.createSeries(ChartView.SeriesTypeScatter, "scatter series", xAxis, yAxis)
        var se = surfaceSeries.selectedPoint
        console.log(se)
    }


}

