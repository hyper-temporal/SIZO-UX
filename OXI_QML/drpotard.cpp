#include "drpotard.h"


#include <QPainter>
#include <QMimeData>


DrPotard::DrPotard(QQuickItem *parent)
    :DrValeur(parent)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
}

DrPotard::~DrPotard(){
}
//independant des dimensions
void DrPotard::syncParams()
{
    _deadz = std::abs(_deadz);
    auto dv_2  = _deadz/2.0;
    _dist = 1.0-_deadz;
    _aL = _centre - dv_2;
    _aR = _centre + dv_2;
    if(_aL < 0.0 ){_aL +=1.0;}
    if(_aR > 1.0 ){_aR -=1.0;}
    _arcstart = _sens?_aL:_aR;
    _arcstart *= 5760.0;
}

///juste pour me souvenir d'avoir fait ça pour rien ... => si t'es fatigué tu vas te coucher
//    auto arclen = v * (1.0-_deadz) ;
//    double a;
//    if(_sens){
//        a = _aL - arclen;
//        if(a<1.0){a += 1.0;}
//    }else{
//        a = _aR+arclen;
//        if(a>1.0){a -= 1.0;}
//    }
//    int x = _cx*width()/2.0 + cos((a)*2.0*M_PI)*100000;
//    int y = _cy*height()/2.0 - sin((a)*2.0*M_PI)*10000;

void DrPotard::setValeur(double v)
{
    _value = v;
    update();
}

void DrPotard::coord2Value(int mx, int my)
{
    auto cx = _cx * width();
    auto cy = _cy * height();
    auto a =  Geometrie::angle(cx,cy,mx,my);
    _value = Geometrie::valeurRotary(a,_aL,_aR,_sens,_dist,_centre);

}



void DrPotard::paint(QPainter *painter){

    auto cx = _cx * width();
    auto cy = _cy * height();
    auto lenmin = std::min(width(),height())*_radius;
    auto rect = QRectF(
                (cx-lenmin/2),
                (cy-lenmin/2),lenmin,lenmin);

    _arclen = ((1.0-_deadz)*5760)*(_value);
    if(_sens){
        _arclen=-_arclen;
    }
    //le peintre a besoins d'un point de depart , d'une size et d'un rectangle
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(_toursel));
    painter->drawRect(QRect(0,0,width(),height()));
    auto r = QRect(0,0,width()-1,height()-1);
    painter->fillRect(r,_fond);
    painter->setBrush(QBrush(_light));
    painter->drawPie(rect,_arcstart,_arclen);
}
