#include "dronde.h"

#include <QPainter>
#include <QMimeData>


DrOnde1D::DrOnde1D(QQuickItem *parent)
    :DrShape(parent)
{
}

DrOnde1D::~DrOnde1D(){

}


void DrOnde1D::linearMorphing(int from, int to)
{
    if(from>to){
        int ermed = from;
        from = to;
        to=ermed;
    }
    if((int)_datas.size()<to)
        return;
    double step = (_datas[to].y - _datas[from].y)/(to-from+1);
    double value = _datas[from].y;
    for(int i=from; i<=to; i++){
        _datas[i].y = value;
        value += step;
    }
}



void DrOnde1D::suiviCurseur(QMouseEvent *me)
{
    auto pind = _cind;
    _cind = getSampleNumber(me);
     auto cY = me->y()<=0? 1.0:
                me->y()>height()?0.0:
                    1.0-(double)me->y()/height();
    auto cval = (cY * 2.0) - 1.0;
    _datas[_cind].y = cval;
    if(pind >=0){
        linearMorphing(pind,_cind);
    }
}

void DrOnde1D::relachement(){
    _cind = -1;
    _pointSelected =-1;
}


int DrOnde1D::getSampleNumber(QMouseEvent *me)
{
    if(me->x()<=0){
        return 0;
    }
    else if(me->x()>=width()){
        return _datas.size()-1;
    }
    double relX = (double)me->x()/width();
    if(_style._interpolation == INTERPOLATION_NONE){
        return  relX * (_datas.size());
    }
//    int nbsegments = _bm.size()-1;

    int nbsegments = _style._looped?_datas.size():_datas.size()-1;
    double sliceWidth = (double)width()/nbsegments;
    double offset = sliceWidth/2;
    uint slicenum =me->x()<=offset?0:
                1+(( me->x()-offset) / sliceWidth);
    return slicenum>_datas.size()-1? _datas.size()-1:
                                  slicenum;
}


void DrOnde1D::mouseReleaseEvent(QMouseEvent *){
    relachement();
}

void DrOnde1D::paintEnveloppe(QPainter &painter, std::vector<data2D> &datas){
    if(_style._looped){
        datas.push_back(datas[0]);
    }
    int nbsegments = datas.size()-1;
    QPoint _pav(0.0, height()*(1.0-( 0.5+ 0.5 * datas[0].y)));
    double tseg_d = (double)width()/(nbsegments);
    double dwidth(0.0);
    for(int i(1);i<=nbsegments;i++){
        painter.setPen(QPen(_style._points));
        auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
        painter.drawRect(r);

        dwidth += tseg_d;
        double vp = 0.5+ 0.5* datas[i].y;
        QPoint p(dwidth, height()*(1.0-vp));
        painter.setPen(QPen(_style._courbe));
        painter.drawLine(_pav , p);
        _pav = p;
    }
    if(_style._looped){
        datas.pop_back();
    }else{
        painter.setPen(QPen(_style._points));
        auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
        painter.drawRect(r);
    }
    //si pas loop le dernier point est a dessiner

}
