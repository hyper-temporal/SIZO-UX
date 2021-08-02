#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>



class TreeItem
{
public:
    enum Roles  {
        RoleNoeud = Qt::UserRole + 0,   //simple noeud a exposer RO
        RoleEdit = Qt::UserRole + 1,    //noeud editable
        RoleDelete = Qt::UserRole + 2,   //delegue l'affichage de tableau a la vue
        RoleArray = Qt::UserRole + 3,   //delegue l'affichage de tableau a la vue
    };
    explicit TreeItem(const QVariant &name, TreeItem *parent = 0);
    ~TreeItem();
    void appendChild(TreeItem *child);
    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    const QString Slug() const;
    const QString Nom() const;
    void setObjet(const QVariant *o);
    const QVariant Objet() const;
    void setDatas(const QVariantList &action);
    QVariant data(int column) const;
    QVariantList datas() const;
    int row() const;
    TreeItem *parent();

    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
private:
    TreeItem *m_parentItem;
    QList<TreeItem*> m_childItems;
    const QVariant * _objet;
    QVariantList m_itemData;
    bool _modifie;
    QString m_itemNom;
    QString m_itemSlug;
};


#endif // TREEITEM_H
