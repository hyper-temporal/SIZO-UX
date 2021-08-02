#ifndef CUSTOMCTRLS_H
#define CUSTOMCTRLS_H

#include <QQuickPaintedItem>

//designe les lcontroles a une seule valeur
//valeur modifiable selon la position de la souris
//
class CustomCtrls
        :public QQuickPaintedItem
{
    Q_OBJECT
//propriete accessibles en QML
//    Q_PROPERTY( QColor  fond      READ  getfond       WRITE setfond     )
public:
    CustomCtrls(QQuickItem *p=nullptr);
    virtual ~CustomCtrls();
//getter sett proprietes
//    void setfond(QColor sty){_style._fond = sty;}
//    QColor getfond()const{return _style._fond;}
//
private:

};



#endif // CUSTOMCTRLS_H
