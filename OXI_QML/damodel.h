#ifndef DAMODEL_H
#define DAMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


class DaModel
        : public QAbstractItemModel
{
    Q_OBJECT
public:
    DaModel( QObject *parent = 0); //rootmodel
    ~DaModel();
    QVariant data(const QModelIndex &index,  int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,  const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const override;
private:
};

#endif // DAMODEL_H
