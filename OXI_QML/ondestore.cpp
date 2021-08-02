#include "ondestore.h"




OndeStore::OndeStore(QObject *parent):
    QObject(parent)
{
}

template<typename T>
const QVariantList fromStdStringList(T dq){
    QVariantList lst;
    for(auto &el : dq){
        lst.push_back(QString::fromStdString(el));
    }
    return lst;
}
template<typename T>
const QVariantList fromObjectList(T dq){
    QVariantList lst;
    for(auto &el : dq){
        lst.push_back(QString::fromStdString(el._name));
    }
    return lst;
}
