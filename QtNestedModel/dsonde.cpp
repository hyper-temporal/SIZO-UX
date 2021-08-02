#include "dsonde.h"

#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DSOnde::DSOnde(QObject *parent):
    QObject(parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
    //generateData(0, 5, 1024){}

    int size;
    for(QVector<QPointF> & v : m_data){
        v.resize(size);
        uint inx(0);
        for(QPointF &vyx : v){
            vyx.rx() = (double)inx++/size;
        }
    }
    for(std::vector<double> & v : m_datastd){
        v.resize(size);
    }
    uint vnum(0);
    for(std::vector<double *> & v : m_datastdopt){
        v.resize(size);
        uint inx(0);
        for(auto & ptv : v){
            m_data[vnum][inx].rx() = (double)inx/size;
            ptv = &(m_data[vnum][inx].ry());
            inx++;
        }
        vnum++;
    }
}

static void conversionTimeSeries(std::vector<double> &stdv, QVector<QPointF> &qtv){
    auto it = qtv.begin();
    for(auto v : stdv){
        it->ry()=v;
        it++;
    }
}

void DSOnde::update(QAbstractSeries *series, uint inx)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(m_data[inx]);
    }
}

void DSOnde::generateData(int type, int rowCount, int colCount)
{
//    qInfo()<<"-P";
    m_data.clear();
    for (int i(0); i < rowCount; i++) {
        QVector<QPointF> points;
        points.reserve(colCount);
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
            switch (type) {
            case 0:
                // data with sin + random component
                y = qSin(3.14159265358979 / 50 * j) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
                x = j;
                break;
            case 1:
                // linear data
                x = j;
                y = (qreal) i / 10;
                break;
            default:
                // unknown, do nothing
                break;
            }
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}



