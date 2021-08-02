#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <qtjson.h>

using namespace QtJson;

class TreeItem;

class TreeModel
        : public QAbstractItemModel
{
    Q_OBJECT
public:
    TreeModel( QObject *parent = 0); //rootmodel
    ~TreeModel();

    Q_INVOKABLE void setModel(QVariant model);
    Q_INVOKABLE void setModelRoot(QString name, QVariantMap root);
    Q_INVOKABLE QVariantList actions(const QModelIndex &index) const ;
    Q_INVOKABLE QVariant objet(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index,  int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    TreeItem *getItem(const QModelIndex &index) const;


    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::EditRole) override;
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;

private:


    static TreeItem * creerNode(const QVariant &label, TreeItem *p = 0);

    template<typename T>
    static QVariantMap Object2QVariant(T &o){
        auto str =ToString(o);          //Serialisable
        auto job = JsonFromString(str); //Qtable
        return job;
    }


    static TreeItem * CreerArbre(QString n, QVariant o,TreeItem *p=nullptr);
    static void setupModelDataProp(const QVariant &datas, TreeItem *parent);
    static void setupModelDataList(const QVariantList &datas, TreeItem *parent);
    static void setupModelDataObject(const QVariantMap &datas, TreeItem *parent);
    static void setupObj(const QVariant &d, TreeItem *parent);


    TreeItem *_rootItem;
    QVariantMap _lobjet;
    QHash<int, QByteArray> _roles_mappings ;
};



#endif // TREEMODEL_H
