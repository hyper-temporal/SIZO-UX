#include "drxy.h"


#include <QPainter>
#include <QMimeData>

DrXY::DrXY(QQuickItem *parent)
    :QQuickPaintedItem(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
}

DrXY::~DrXY(){
}

void DrXY::syncParams()
{
    _rminX = std::min(_minX,_maxX);
    _rmaxX = std::max(_minX,_maxX);
    _sensinverseX = _rminX != _minX;
    _distX = std::abs(_rmaxX-_rminX);
    _changementdesigneX = (_minX<0 && _maxX >0) || (_minX>0 && _maxX<0);

    _rminY = std::min(_minY,_maxY);
    _rmaxY = std::max(_minY,_maxY);
    _sensinverseY = _rminY != _minY;
    _distY = std::abs(_rmaxY-_rminY);
    _changementdesigneY = (_minY<0 && _maxY >0) || (_minY>0 && _maxY<0);

    //_rel0 est la distance par rapport au minimum
    if(!_changementdesigneX){
        _rel0X = 0.0;
    }else{
        _rel0X = std::abs(_rminX/_distX);
    }

    if(!_changementdesigneY){
        _rel0Y = 0.0;
    }else{
        _rel0Y = std::abs(_rminY/_distY);
    }

}

void DrXY::setValeurs(double vx, double vy)
{
    _valrelX = (vx-_rminX)/_distX;
    _valX = _sensinverseX?
                _rmaxX - _valrelX*_distX:
                _rminX + _valrelX*_distX;


    _valrelY = (vy-_rminY)/_distY;
    _valY = _sensinverseY?
                _rmaxY - _valrelY*_distY:
                _rminY + _valrelY*_distY;
    update();
}

void DrXY::coord2Values(int mx, int my)
{
    int limx = mx>width()?width():mx<0?0:mx;
    _valrelX = (double)limx/width();
    int limy = my>height()?height():my<0?0:my;
    _valrelY = (double)limy/height();

    _valX = _sensinverseX?_rminX + (1.0-_valrelX)*_distX:_rminX + _valrelX*_distX;
    _valY = _sensinverseY?_rminY + (1.0-_valrelY)*_distY:_rminY + _valrelY*_distY;
//    Debug::toCoutWithLegend("valeurX:",_valX);
//    Debug::toCoutWithLegend("valeurY:",_valY);
}



void DrXY::paint(QPainter *painter){
    painter->setRenderHint(QPainter::Antialiasing, true);

    //une croix placée en valrel(x,y)
    painter->setPen(_light);
    auto jx = _valrelX*width();
    auto jy = _valrelY*height();

    painter->drawLine( jx-6,jy,jx+6,jy);
    painter->drawLine( jx,jy-6,jx,jy+6);

}


void DrXY::mousePressEvent(QMouseEvent *me){
    _isdragging =true;
}

void DrXY::mouseMoveEvent(QMouseEvent *me){
    if(_isdragging){
        coord2Values(me->x(),me->y());
        update();
    }
}

void DrXY::mouseReleaseEvent(QMouseEvent *me){
    _isdragging =false;
}
