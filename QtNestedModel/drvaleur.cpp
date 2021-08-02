#include "drvaleur.h"


DrValeur::DrValeur(QQuickItem *p)
    :QQuickPaintedItem(p)
{
}

DrValeur::~DrValeur(){
}

void DrValeur::mousePressEvent(QMouseEvent *me){
    _isdragging =true;
}

void DrValeur::mouseMoveEvent(QMouseEvent *me){
    if(_isdragging){
        coord2Value(me->x(),me->y());
        update();
    }
}

void DrValeur::mouseReleaseEvent(QMouseEvent *me){
    _isdragging =false;
}
