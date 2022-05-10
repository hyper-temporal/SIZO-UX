#include "drshape.h"

#include <QPainter>

static QColor
    _clr_backlite(200 ,180,220),
    _clr_GrayLine(150 ,150,150),
    _clr_Black (0x0,0x0,0x0),
    _clr_White (0xff ,0xff,0xff),
    _clr_violet(0xaa ,0x0,0xff),
    _clr_Red (0xff,0,0),
    _clr_Blue (0,128,255),
    _clr_border (150,190,230)
;

DrShape::DrShape(QQuickItem *p)
    :QQuickPaintedItem(p)
    ,_datas(testvec())
    ,_pixmax(16)
    ,_pointSelected(-1)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
}
DrShape::~DrShape(){

}

void DrShape::setData(std::vector<data2D> dt){
    _datas=dt;
}


static data2D GetIndexBorne(std::vector<data2D> &v, int index){
    if(index<=0){
        return v.front();
    }else if((uint)index >= v.size()){
        return v.back();
    }else{
        return v[index];
    }
}

static void DessineSamplesEnSurnombre(double width, double height,QPainter&painter, std::vector<data2D> &datas){
    double lv(0.0);
    int linx(0);
    int ldatainx = -1;
    for(int inx(0);inx <= width;inx++){
        auto prop = (double)inx/width;
        int datainx =  prop*(datas.size());
        double vp = 0.5+0.5*datas[datainx].y;
        if( ldatainx != datainx){
            ldatainx = datainx;
            double v = height*(1.0-vp);
            painter.drawLine( QLine(QPoint(linx,lv),QPoint(inx,lv)));
            if(inx > 0 && inx < width){
                painter.drawLine( QLine(QPoint(inx,lv),QPoint(inx,v)));
            }
            lv = v;
            linx = inx;
        }
    }
}

void DrShape::mousePressEvent(QMouseEvent *me){
    if(_datas.empty())return;
    _pointSelected = getSampleNumber(me);
    update();
}
void DrShape::mouseMoveEvent(QMouseEvent *me){
    if(_datas.empty())return;
    suiviCurseur(me);
    update();

}
void DrShape::mouseReleaseEvent(QMouseEvent *){
    if(_datas.empty())return;

}

void DrShape::paint(QPainter *painter){
    if(_datas.empty())return;
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(_style._bord));
    painter->drawRect(QRect(0,0,width(),height()));
    painter->fillRect(QRect(0,0,width()-1,height()-1),_style._fond);
    if(_datas.empty())return;

    painter->setPen(QPen(_style._centre));
    painter->drawLine(QPoint(0, height()/2),
                     QPoint(width(), height()/2));
    painter->setPen(QPen(_clr_White));
    auto &copy = _datas;

    if(copy.size() >= width()){
        DessineSamplesEnSurnombre(width(),height(), *painter,_datas);
        return;
    }
    switch (_style._interpolation)
    {
    case INTERPOLATION_NONE:
        paintDomainClassic(*painter,copy);
        break;
    case INTERPOLATION_LINEAR:
        paintEnveloppe(*painter,copy);
        break;
    case INTERPOLATION_HERMITE:
        paintInterpolationHermite(*painter,copy);
        break;
    default:
        paintDomainClassic(*painter,copy);
        break;
    }
}

void DrShape::paintInterpolationHermite(QPainter&painter, std::vector<data2D> &datas){
    QPoint _pav,_pcu;
    if(_style._looped){
        datas.push_back(datas[0]);
    }
    std::vector<data2D> out(width());
//    AudioUtil::interpoler2D(datas,out);

    for(int i(0);i<width();i++){
        double vp = 0.5+0.5* out[i].y;
        _pav = _pcu;
        _pcu=QPoint(i, height()*(1.0-vp));
        if(i>0){
            painter.drawLine(_pav , _pcu);
        }
    }
    //dessin des points
    int nbsegments = datas.size()-1;
    _pav = QPoint(0.0, height()*(1.0-( 0.5+ 0.5*datas[0].y)));
    double tseg_d = (double)width()/(nbsegments);
    double dwidth(0.0);
    for(int i(1);i<=nbsegments;i++){
        painter.setPen(QPen(_style._points));
        auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
        painter.drawRect(r);
        dwidth += tseg_d;
        double vp = 0.5+ 0.5* datas[i].y;
        QPoint p(dwidth, height()*(1.0-vp));
        _pav = p;
    }
    if(_style._looped){
        datas.pop_back();
    }else{
        painter.setPen(QPen(_style._points));
        auto r =QRect(_pav.rx()-3,_pav.ry()-3,6,6);
        painter.drawRect(r);
    }
}

void DrShape::paintDomainClassic(QPainter&painter, std::vector<data2D> &datas){
    int nbsegments = datas.size();
    QPoint pav(0.0, height()*(1.0-( 0.5+ 0.5*datas[0].y)));
    double tseg_d = (double)width()/(nbsegments);
    double dwidth(0.0);
    for(int inx(1);inx <= nbsegments;inx++){
        dwidth += tseg_d;
        double vp = 0.5+ 0.5* datas[inx-1].y;
        double h =  height()*(1.0-vp);
        QPoint npo(pav);
        npo.setY(h);
        painter.drawLine( QLine(pav,npo));
        QPoint npv(dwidth,h);
        painter.drawLine( QLine(npo,npv));
        pav = npv;
    }
}


