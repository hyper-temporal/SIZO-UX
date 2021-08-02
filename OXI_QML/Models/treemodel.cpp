#include "treemodel.h"
#include "treeitem.h"

#include <QStringList>
#include <qdebug.h>

using namespace QtJson;



static QVariantList actionsPersistences = {
    "initialize", //selection de preset
    "collecter", //cliquer pour addUp a la collection
};
static QVariantList actionsCollections = {
    "gerer",
    "chercher",
    "dupliquer",
    "classer",
};
static QVariantList actionsArray = {
    "addUp",  //addUp un element a un tableau
    "effacer", //effacer  les elements d'un tableau (tout,selection...)
    "editer", //cliquer pour entrer dans le mode d'édition
};

static QVariantList actionsElement = {
    "detruire", //seul un element de taleau peut etre detruit
    "editer", //cliquer pour entrer dans le mode d'édition
};

static QVariantList actionsObjet = {
    "editer", //cliquer pour entrer dans le mode d'édition
};
static QVariantList actionsPropriete = {
    "modifier",
};


TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
    ,_rootItem(nullptr)
{
    _roles_mappings[TreeItem::RoleNoeud] = "key";
    _roles_mappings[TreeItem::RoleEdit] = "edit";
    _roles_mappings[TreeItem::RoleDelete] = "delete";
    _roles_mappings[TreeItem::RoleArray] = "array";
    QVariantMap map;
    setModelRoot("vide",map);
}
void TreeModel::setModel(QVariant model){
    setModelRoot("session",model.toMap());
}

void TreeModel::setModelRoot(QString name,QVariantMap root)
{
    if(_rootItem != nullptr){
        delete _rootItem;
    }
//    qInfo()<< "setModelRoot:"+name;
    beginResetModel();
    _lobjet = root;
    _rootItem = CreerArbre(name,_lobjet);
    _rootItem->setDatas(actionsArray);
    endResetModel();

}

TreeModel::~TreeModel()
{
    delete _rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return _rootItem->columnCount();
}


QHash<int,QByteArray> TreeModel::roleNames() const
{
    return _roles_mappings;
}


QVariantList TreeModel::actions(const QModelIndex &index) const {
    if (!index.isValid()){
        return QVariantList();
    }
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return  item->datas();

}
QVariant TreeModel::objet(const QModelIndex &index) const{
    if (!index.isValid()){
        return QVariant();
    }
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    return item->Objet();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
//    qInfo()<<"data : "<< role ;
//    qInfo()<< _roles_mappings[role] ;
    if (!index.isValid()){
        return QVariant();
    }
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
//    qInfo()<< item->Slug();
    return item->Nom();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;
    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();
    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();
    if (parentItem == _rootItem)
        return QModelIndex();
    return createIndex(parentItem->row(), 0, parentItem);
}


int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

TreeItem * TreeModel::creerNode(const QVariant &label, TreeItem *p ){
    auto nel = new TreeItem(label,p);
    return nel;
}

TreeItem * TreeModel::CreerArbre(QString name, QVariant o,TreeItem *p){
    auto item = creerNode(name,p);
    setupObj(o,item);
    return item;
}

void TreeModel::setupObj(const  QVariant &d, TreeItem *nn){
//    qInfo() << d.typeName();
//    qInfo() <<d.type();
    nn->setObjet(&d);
    if(d.type() ==QVariant::Map ){
        auto dd = (QVariantMap*)(&d);
        setupModelDataObject(*dd,nn);
    }
    else if(d.type() ==QVariant::List ){    ///UN ARRAY
        auto dd = (QVariantList*)(&d);
        setupModelDataList(*dd,nn);
    }
    else{
        setupModelDataProp(d,nn);
    }
}

void TreeModel::setupModelDataProp(const QVariant &data, TreeItem *parent){
    QList<QVariant> qlv;
    qlv<<data<<"edit";
    auto nn = creerNode(data,parent);
    parent->appendChild(nn);
    //pas de referencement de l'objet supplementaire
}

void TreeModel::setupModelDataList(const QVariantList &datas, TreeItem *parent)
{
    uint cnt(0);
    for(auto &d : datas){
        QString s;
        s = "[" + QString::fromStdString(std::to_string(cnt++)) + "]";
        auto nn = creerNode(s,parent);
        nn->setDatas(actionsArray);
        parent->appendChild(nn);
        setupObj(d,nn);
    }
}

//lui passer une ref
void TreeModel::setupModelDataObject( const QVariantMap &datas, TreeItem *parent)
{
    for (QMap<QString,QVariant>::const_iterator it = datas.cbegin(), end = datas.cend(); it != end; ++it) {
        const QString kn = it.key();
//        qInfo()<< "cle: \t" << kn ;
        auto nn = creerNode(kn,parent);
        nn->setDatas(actionsArray);
        parent->appendChild(nn);
        auto &d = it.value();
        setupObj(d,nn);
    }
}



//EDIT


bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = _rootItem->removeColumns(position, columns);
    endRemoveColumns();

    if (_rootItem->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
    success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}



TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return _rootItem;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
        return false;

    bool result = _rootItem->setData(section, value);

    if (result)
        emit headerDataChanged(orientation, section, section);

    return result;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return _rootItem->data(section);

    return QVariant();
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginInsertColumns(parent, position, position + columns - 1);
    success = _rootItem->insertColumns(position, columns);
    endInsertColumns();

    return success;
}

bool TreeModel::insertRows(int position, int rows,  QModelIndex const&parent)
{
    TreeItem *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->insertChildren(position, rows, _rootItem->columnCount());
    endInsertRows();

    return success;
}
