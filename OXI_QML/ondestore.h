#ifndef ONDESTORE_H
#define ONDESTORE_H
#include    <QtCore/QObject>
#include    <QtCharts/QAbstractSeries>
#include    "Models/qtoutils.h"

/*
 * use case
 *      create graph
 *      create sequence
 *
 *
*/

class OndeStore
        :public QObject
{

    Q_OBJECT

public:
    explicit OndeStore(
            QObject *parent = 0);
    Q_INVOKABLE QVariant getSession() const{
        return QVariant();
    }
private:
};


#endif // ONDESTORE_H
