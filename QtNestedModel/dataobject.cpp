#include <QDebug>
#include "dataobject.h"

DataObject::DataObject(QObject *parent)
    : QObject(parent)
    ,m_objet(QVariant())
{
}

DataObject::DataObject(const QVariant &objet, QObject *parent)
    : QObject(parent),
      m_objet(objet)
{
}

QVariant DataObject::objet() const
{
    return m_objet;
}

void DataObject::setObjet(const QVariant &objet)
{
    if (objet != m_objet) {
        m_objet = objet;
        emit objetChanged();
    }
}
