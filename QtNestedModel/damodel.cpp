#include "damodel.h"
#include <QDebug>


DaModel::DaModel( QObject *parent){
}

DaModel::~DaModel(){
}

QVariant DaModel::data(const QModelIndex &index, int role) const{
    return QVariant();
}

QVariant DaModel::headerData(int section, Qt::Orientation orientation, int role ) const{
    return QVariant();
}

Qt::ItemFlags DaModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

QModelIndex DaModel::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    return QModelIndex();
}

QModelIndex DaModel::parent(const QModelIndex &index) const{
    if (!index.isValid())
        return QModelIndex();
    return QModelIndex();
}


int DaModel::rowCount(const QModelIndex &parent) const{
    return 0;
}

int DaModel::columnCount(const QModelIndex &parent) const{
    return 0;
}

QHash<int,QByteArray> DaModel::roleNames() const{
    return {};

}
