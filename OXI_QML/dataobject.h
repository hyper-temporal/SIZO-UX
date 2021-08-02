#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include  "Models/qtoutils.h"

class DataObject
        : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant objet READ objet WRITE setObjet NOTIFY objetChanged)

public:
    DataObject(QObject *parent=0);
    DataObject(const QVariant &objet, QObject *parent= nullptr);
    QVariant objet() const;
    void setObjet(const QVariant &objet);
signals:
    void objetChanged();
private:
    QVariant m_objet;
};

#endif // DATAOBJECT_H
