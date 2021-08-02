#ifndef IOMODEL_MIDIIN_H
#define IOMODEL_MIDIIN_H

#include <QAbstractListModel>
#include "qtoutils.h"
#include <deque>
#include <boio.h>

Q_DECLARE_METATYPE(QModelIndex)



template<typename T, typename C>
class GenericModel
        :public QAbstractListModel
{
public:
GenericModel(C &r, QObject *parent)
    : QAbstractListModel(parent)
    ,_collec(r)
{}
virtual ~GenericModel(){}
void addObject(const QVariant &v)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    auto zob = QtOutils::QVariant2Object<T>(v);
    _collec.push_back(zob);
    endInsertRows();
}

int rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return _collec.size();
}

QVariant data(const QModelIndex & index, int role ) const {
    if (index.row() < 0 || (uint)index.row() >= _collec.size())
        return QVariant();
    const auto &zob = _collec[index.row()];
    return roleToData(zob,role);
}

protected:
    virtual QVariant roleToData(const IOAliases &v,int role)const=0;
    virtual QHash<int, QByteArray> roleNames() const=0;
    C &_collec;
};


class IOModel
        :public GenericModel<IOAliases,std::deque<IOAliases>>
{
    Q_OBJECT
public:
    virtual ~IOModel(){}
    IOModel(std::deque<IOAliases> &r, QObject *parent=0);
    Q_INVOKABLE void changerAlias(int inx, const QVariant &value);
    Q_INVOKABLE void etatIO(int inx, bool st);

    QVariant roleToData(const IOAliases &v, int role)const;
protected:
    QHash<int, QByteArray> roleNames() const ;
};

#endif // IOMODEL_MIDIIN_H
