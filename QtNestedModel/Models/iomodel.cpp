#include "iomodel.h"


enum IORoles {
    NomRole = Qt::UserRole + 1,
    AliasRole,
    PluggedRole,
    UsedRole,
};


QVariant IOModel::roleToData(const IOAliases &v,int role)const{
    if (role ==NomRole)
        return QString::fromStdString(v._name);
    else if (role == AliasRole)
        return QString::fromStdString(v._nick);
    else if (role == PluggedRole)
        return QVariant::fromValue(v._plugged);
    else if (role == UsedRole)
        return QVariant::fromValue(v._actif);
    return QVariant();
}

QHash<int, QByteArray> IOModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NomRole]      = "name"     ;
    roles[AliasRole]    = "nick"  ;
    roles[UsedRole]     = "actif"   ;
    roles[PluggedRole]  = "plugged" ;
    return roles;
}

IOModel::IOModel(std::deque<IOAliases> &r, QObject *parent)
    : GenericModel(r,parent)
{}
void IOModel::changerAlias(int inx, const QVariant &value){
    qInfo()<< "ROW" << inx;
    if(inx <0 || inx >= (int)_collec.size())return ;
    IOAliases &item = _collec[inx];
    item._nick = value.toString().toStdString();
    auto i = index(inx,0);
    emit dataChanged(i,i);
}

void IOModel::etatIO(int inx, bool st){
    qInfo()<< "ROW" << inx;
    if(inx <0 || inx >= (int)_collec.size())return ;
    IOAliases &item = _collec[inx];
    item._actif = st;
    auto i = index(inx,0);
    emit dataChanged(i,i);
}


