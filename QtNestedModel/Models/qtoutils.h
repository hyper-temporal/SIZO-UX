#ifndef QTOUTILS_H
#define QTOUTILS_H


#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>
#include <QMap>
#include <qtjson.h>
#include <json.hpp>
#include <dataobject.h>

QT_CHARTS_USE_NAMESPACE
Q_DECLARE_METATYPE(QAbstractSeries *)



class QtOutils
{
public:

template<typename T>
static T QVariant2Object(const QVariant &m){
    bool ok(false);
    auto str = QtJson::serializeStr(m,ok).toStdString();
    nlohmann::json j = nlohmann::json::parse(str);
    auto zob = j.get<T>();
    return zob;
}

template<typename T>
static QVariantMap Object2QVariant(T &o){

    auto str =ToString(o);          //Serialisable
    auto job = QtJson::JsonFromString(str); //Qtable
    return job;
}



template<typename T,typename C>
static void variantToCollec(QVariant &v, C &collec){
    QVariantList list = v.toList();
    collec.clear();
//    collec.reserve(list.size());
    for(auto &el : list){
        auto o = QtOutils::QVariant2Object<T>(el);
        collec.push_back(o);
        qInfo()<<el;
    }
}
template<typename C>
static QVariant collectiontovariant(C &collec ){
    QVariantList list;
    for(auto &n : collec){
        list.push_back(QtOutils::Object2QVariant(n));}
    return list;
}



template<typename C>
static QVariant stringList2Variant(C &collec ){
    QStringList list;
      for(auto &n : collec ){
        list.append(QString::fromStdString(n));}
    return QVariant::fromValue(list);
}

template<typename T>
static QVariant fromVector(std::vector<T> t ){
    QVector<T> list =QVector<T>::fromStdVector(t);
    return QVariant::fromValue(list);
}

template<typename T>
static void fromVector(QXYSeries &serie, const std::vector<T> &t ){
    serie.clear();
    for(auto v : t){
        serie.append(v[0],v[1]);
    }
}



};

#endif // QTOUTILS_H
