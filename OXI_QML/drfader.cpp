#include "drfader.h"


#include <QPainter>
#include <QMimeData>

DrFader::DrFader(QQuickItem *parent)
    :DrValeur(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
}

DrFader::~DrFader(){
}

void DrFader::syncParams()
{
    _rmin = std::min(_min,_max);
    _rmax = std::max(_min,_max);
    _sensinverse = _rmin != _min;
    _dist = std::abs(_rmax-_rmin);
    _changementdesigne = bool(((_min<0) && (_max >0)) || ((_min>0) && (_max <0)));

    //_rel0 est la distance par rapport au minimum
    if(!_changementdesigne){
        _rel0 = 0.0;
    }else{
        _rel0 = std::abs(_rmin/_dist);
    }

}

void DrFader::setValeur(double v)
{
    _valrel = (v-_rmin)/_dist;
    _value = _sensinverse?
                _rmax - _valrel*_dist:
                _rmin + _valrel*_dist;

    update();
}

void DrFader::coord2Value(int mx, int my)
{
    if(_horiz){
        int limx = mx>width()?width():mx<0?0:mx;
        _valrel = (double)limx/width();
    }else{
        int limy = my>height()?height():my<0?0:my;
        _valrel = 1.0-(double)limy/height();
    }
    if(_sensinverse ){
        _valrel = 1.0-_valrel;
//        _rel0 =1.0 - _rel0;
    }

    _value = _rmin + _valrel*_dist;
//    Debug::toCoutWithLegend("_value:",_value);
//    Debug::toCoutWithLegend("_valrel:",_valrel);
}



void DrFader::paint(QPainter *painter){
    painter->setRenderHint(QPainter::Antialiasing, true);

    double rgmin,rgval,rgmax;

    if(_changementdesigne){
        if(_value< 0.0){
            rgmin = _valrel ;
            rgval =  _rel0 -_valrel ;
            rgmax =  1.0 - _rel0 ;
        }else{
            rgmin = _rel0 ;
            rgmax =  1.0-_valrel;
            rgval =  _valrel - _rel0  ;
        }
    }else{
        rgmin = 0.0;
        rgval =  _valrel  ;
        rgmax =  1.0-_valrel  ;
    }

//    qInfo()<< "rgmin" << rgmin << "rgval" << rgval << "rgmax" <<rgmax ;
    QRect rap,rva,rav;
    if(_horiz){
        if(_sensinverse){
            rav = QRect(0,0,rgmax*width(),height());
            rva = QRect(rav.width(),0,rgval*width(),height());
            rap = QRect(rav.width()+rva.width(),0,rgmin*width(),height());
        }
        else{
            rav = QRect(0,0,rgmin*width(),height());
            rva = QRect(rav.width(),0,rgval*width(),height());
            rap = QRect(rav.width()+rva.width(),0,rgmax*width(),height());
        }
    }else{
        if(_sensinverse){
            rav = QRect(0,0,width(),(rgmin)*height());
            rva = QRect(0,rav.height(),width(),(rgval)*height());
            rap = QRect(0,rav.height()+rva.height(),width(),(rgmax)*height());
        }
        else{
            rav = QRect(0,0,width(),(rgmax)*height());
            rva = QRect(0,rav.height(),width(),(rgval)*height());
            rap = QRect(0,rav.height()+rva.height(),width(),(rgmin)*height());
        }
    }
    QBrush bf(_fond);
    QBrush bl(_light);

    painter->fillRect(rav,bf);
    painter->fillRect(rap,bf);
    painter->fillRect(rva,bl);

    if(_changementdesigne){

        //valeur de la portion entre le min et le 0
        if(_horiz){
            auto v0 = _sensinverse?(1.0-_rel0)*width():_rel0*width();
            painter->setPen(_repere);
            painter->drawLine(v0,0,v0,height());
        }else{
            auto v0 = _sensinverse?_rel0*height():(1.0-_rel0)*height();
            painter->setPen(_repere);
            painter->drawLine(0,v0,width(),v0);
        }
    }
}
