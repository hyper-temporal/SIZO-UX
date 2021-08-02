#ifndef DSONDE_H
#define DSONDE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>


QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class DSOnde
        :public QObject
{
    Q_OBJECT
public:
    explicit DSOnde(
            QObject *parent = 0);
Q_SIGNALS:
public slots:
    void generateData(int type, int rowCount, int colCount);
    void update(QAbstractSeries *series,uint inx);
private:
    QVector<QVector<QPointF>> m_data;
    std::vector<std::vector<double>> m_datastd;
    std::vector<std::vector<double *>> m_datastdopt;
};


#endif // DSONDE_H
