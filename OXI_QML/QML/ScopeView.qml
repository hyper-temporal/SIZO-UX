import QtQuick 2.0
import QtCharts 2.2

Item{
    id : chartobj
    ChartView {
        id: chartView
//        plotArea:  {Qt.rect(0,0,width,height)}
        animationOptions: ChartView.NoAnimation
        theme: ChartView.ChartThemeDark
        title: ""
//        Legend.visible: false
        anchors.fill: parent

        ValueAxis {
            id: axisY1
            min: -1.0
            max: 1.0
            labelsVisible: false
            gridVisible: false
            lineVisible: false
            titleVisible: false
            minorGridVisible: false
        }

        ValueAxis {
            id: axisY2
            min: -1.0
            max: 1.0
            labelsVisible: false
            gridVisible: false
            lineVisible: false
            titleVisible: false
            minorGridVisible: false

        }

        ValueAxis {
            id: axisX
            min: 0.0
            max: 1.0
            labelsVisible: false
            gridVisible: false
            lineVisible: false
            titleVisible: false
            minorGridVisible: false

        }

        LineSeries {
            id: lineSeries1
            name: ""
            axisX: axisX
            axisY: axisY1
            useOpenGL: true
        }
        LineSeries {
            id: lineSeries2
            name: ""
            axisX: axisX
            axisYRight: axisY2
            useOpenGL: true
        }

        Timer {
            id: refreshTimer
            interval: 1 / 30 * 1000
            running: true
            repeat: true
            onTriggered: {
                dataSource.update(chartView.series(0),0);
                dataSource.update(chartView.series(1),1);
            }
        }

        function changeSeriesType(type) {
            chartView.removeAllSeries();

            // Create two new series of the correct type. Axis x is the same for both of the series,
            // but the series have their own y-axes to make it possible to control the y-offset
            // of the "signal sources".
            if (type == "line") {
                var series1 = chartView.createSeries(ChartView.SeriesTypeLine, "signal 1",
                                                     axisX, axisY1);
                series1.useOpenGL = chartView.openGL

                var series2 = chartView.createSeries(ChartView.SeriesTypeLine, "signal 2",
                                                     axisX, axisY2);
                series2.useOpenGL = chartView.openGL
            } else {
                var series1 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 1",
                                                     axisX, axisY1);
                series1.markerSize = 2;
                series1.borderColor = "transparent";
                series1.useOpenGL = chartView.openGL

                var series2 = chartView.createSeries(ChartView.SeriesTypeScatter, "signal 2",
                                                     axisX, axisY2);
                series2.markerSize = 2;
                series2.borderColor = "transparent";
                series2.useOpenGL = chartView.openGL
            }
        }

        function createAxis(min, max) {
            // The following creates a ValueAxis object that can be then set as a x or y axis for a series
            return Qt.createQmlObject("import QtQuick 2.0; import QtCharts 2.0; ValueAxis { min: "
                                      + min + "; max: " + max + " }", chartView);
        }

        function setAnimations(enabled) {
            if (enabled)
                chartView.animationOptions = ChartView.SeriesAnimations;
            else
                chartView.animationOptions = ChartView.NoAnimation;
        }

        function changeRefreshRate(rate) {
            refreshTimer.interval = 1 / Number(rate) * 1000;
        }
    }
}
