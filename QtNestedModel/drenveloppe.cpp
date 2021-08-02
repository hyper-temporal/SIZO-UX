#include "drenveloppe.h"

#include <QPainter>
#include <QMimeData>
#include <math.h>


DrGanttOptim::DrGanttOptim(QQuickItem *parent)
    :DrShape(parent)
{
    _style._interpolation = 1;
    _style._looped = false;

}

DrGanttOptim::~DrGanttOptim(){

}
void DrGanttOptim::suiviCurseur(QMouseEvent *me){
    if(_pointSelected<0)return;
    auto cY = me->y()<=0?1.0:
                me->y()>height()?0.0:
                    1.0-(double)me->y()/height();
    auto cval = (cY * 2.0) - 1.0;
    auto &_selected = _datas[_pointSelected];
    _selected.y = cval;
    if(         _pointSelected>0
            &&  _pointSelected < (int)(_datas.size()-1))
    {
        auto &ptav =  _datas[_pointSelected-1];
        auto &ptap =  _datas[_pointSelected+1];
        auto cX = me->x()<=0? 0.0:
                    me->x()>width()?1.0:
                                    (double)me->x()/width();
        if(ptav.x> cX){
            cX = ptav.x;
        }
        else if(ptap.x< cX){
            cX = ptap.x;
        }
        _selected.x = cX;
    }
    update();

}


void DrGanttOptim::mousePressEvent(QMouseEvent *me){
    _pointSelected = getSampleNumber(me);
    if(_pointSelected >=0){
        update();
    }
}

void DrGanttOptim::mouseReleaseEvent(QMouseEvent *){
    _pointSelected = -1;
    update();
}

static int trouverIndexesAuPlusProche(
        std::vector<data2D>& ve,
        double vx, double vy,
        double ratioX_Y,
        double maxdist=0.0
        )
{
//    Debug::toCoutWithLegend("mX",vx);
//    Debug::toCoutWithLegend("mY",vy);

    int inx (-1);
    double dist(std::numeric_limits<double>::infinity()) ;

    for(uint i(0); i < ve.size(); i++){
        //        Debug::toCoutWithLegend("_____x", ve[i][0]);
        //        Debug::toCoutWithLegend("_____y", ve[i][1]);
        //        Debug::toCoutWithLegend("mX",vx);
        //        Debug::toCoutWithLegend("mY",vy);
        double relpx = ve[i].x;
        double relpy = ve[i].y;
        double dista = ((vx - relpx)*ratioX_Y);
        double distb = ((vy - relpy)/(ratioX_Y));
        //        Debug::toCoutWithLegend("dista",dista);
        //        Debug::toCoutWithLegend("distb",distb);
        double ndist = std::sqrt((dista*dista) + (distb*distb));
//        Debug::toCoutWithLegend("ndist",ndist);
//        Debug::toCoutWithLegend("maxdist",maxdist);
        if(ndist<maxdist && ndist <=  dist){
            inx=i;
            dist=ndist;
        }
    }
    return inx;
}


int DrGanttOptim::getSampleNumber(QMouseEvent *me)
{
    if(width()<=0)return -1;
    double maxdist = (double)_pixmax/std::min(width(),height());
    double ratioX_Y = (double)width()/(height());
    double relX =  (double)me->x()/width();
    double relY =  -1.0+((1.0-(double)me->y()/height())*2.0);
    return trouverIndexesAuPlusProche(_datas,relX,relY,ratioX_Y,maxdist);

}


void DrGanttOptim::paintEnveloppe(QPainter&painter,  std::vector<data2D> &datas){

    int nbsegments = datas.size()-1;
    QPoint _pav(0.0, height()*(1.0-( 0.5+ 0.5 * datas[0].x)));
    for(int i(1);i<=nbsegments;i++){
        if(i-1==_pointSelected){
            painter.setPen(QPen(_style._points));
            auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
            painter.drawRect(r);
        }
        double vpx = datas[i].x;
        double vpy = 0.5+ 0.5* datas[i].y;
        QPoint p(width()*vpx, height()*(1.0-vpy));
        painter.setPen(QPen(_style._courbe));
        painter.drawLine(_pav , p);
        _pav = p;
    }
    if(_pointSelected ==nbsegments ){
        painter.setPen(QPen(_style._points));
        auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
        painter.drawRect(r);
    }

}
