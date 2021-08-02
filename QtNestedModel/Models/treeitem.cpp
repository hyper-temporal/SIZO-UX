#include <QStringList>
#include <QDebug>
#include "treeitem.h"


TreeItem::TreeItem(const QVariant &name, TreeItem *parent)
    :_objet(nullptr)
    ,_modifie(false)
{
    m_parentItem = parent;
    m_itemNom = name.toString();
    m_itemSlug = parent!=nullptr?
                QString(parent->Slug()) + QString(".")+QString(m_itemNom):
                QString(m_itemNom);
//    qInfo() << m_itemSlug;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}
const QString TreeItem::Slug() const
{
    return m_itemSlug;
}
const QString TreeItem::Nom() const
{
    return m_itemNom;
}
void TreeItem::setObjet(const QVariant *o){
    _objet = o;
    _modifie = true;
}

const QVariant TreeItem::Objet() const
{
    if(_objet != nullptr)
        return *_objet;
    return QVariant();
}
void TreeItem::setDatas(const QVariantList &actions){
    m_itemData = actions;
}

QVariant TreeItem::data(int column) const
{
    return m_itemData.value(column);
}
QVariantList TreeItem::datas() const
{
    return m_itemData;
}
TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}




bool TreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVariant data(columns);
        TreeItem *item = new TreeItem(data, this);
        m_childItems.insert(position, item);
    }

    return true;
}
//! [7]

//! [8]
bool TreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.insert(position, QVariant());

    foreach (TreeItem *child, m_childItems)
        child->insertColumns(position, columns);

    return true;
}
//! [8]



//! [10]
bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);

    return true;
}
//! [10]

bool TreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > m_itemData.size())
        return false;

    for (int column = 0; column < columns; ++column)
        m_itemData.removeAt(position);

    foreach (TreeItem *child, m_childItems)
        child->removeColumns(position, columns);

    return true;
}

//! [11]
bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_itemData.size())
        return false;

    m_itemData[column] = value;
    return true;
}

