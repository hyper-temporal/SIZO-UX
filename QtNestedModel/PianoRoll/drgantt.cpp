#include "drgantt.h"
#include <QPainter>
#include <QLineF>
#include <QSGSimpleRectNode>
#include <QDebug>

static QColor
_clr_backlite(200 ,180,220),
_clr_GrayLine(150 ,150,150),
_clr_Black (0,0,0),
_clr_White (255 ,255,255),
_clr_violet(180 ,0,255),
_clr_Red (255,0,0),
_clr_Orange (200,64,64),
_clr_Blue (128,200,255),
_clr_Green (128,255,200),
_clr_border (150,190,230)
;

DrGanttVue::DrGanttVue(QQuickItem *p)
    :QQuickPaintedItem(p)
{}

DrGantt::DrGantt(QQuickItem *p)
    :DrGanttVue(p)
    ,_edited(nullptr)
    ,_hovered(nullptr)
    ,_drag_V(false)
    ,_drag_H(false)
    ,_extend_HL(false)
    ,_extend_HR(false)
    ,_makedirty(true)
    ,_deplacement(false)
{
    //    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    this->setCursor(QCursor(_style._curseurBase));
    //    setFlag(ItemHasContents, true);
    //    setFlag(ItemAcceptsInputMethod, true);
}
DrGantt::~DrGantt(){
}


double DrGantt::getLength()const {
    return _model.getLength();
}
void DrGantt::setDuree(double v){
    _model.setDuree(v);
}
double DrGantt::getSparPix()const {
    return _model.getSparPix();
}
void DrGantt::setsecondeParPixel(double v){
    _model.setsecondeParPixel(v);
    actualiseVue();
}
double DrGantt::getpixperline()const {
    return _model.getpixperline();
}
void DrGantt::setpixperline(double v){
    _model.setpixperline(v);
    actualiseVue();
}
void DrGantt::addCentreX(double v){
    _model.addCentreX(v);
    actualiseVue();
}
void DrGantt::addCentreY(double v){
    _model.addCentreY(v);
    actualiseVue();
}
void DrGantt::actualiseVue(){
    retailleVue();
    _makedirty = true;
    update();
}

//relacher le segment
void DrGantt::mouseReleaseEvent(QMouseEvent * me){
    _drag_H=false;
    _drag_V=false;
    _extend_HL=false;
    _extend_HR=false;
    _deplacement =false;
    auto p = me->pos();

    _pointAvant = {p.rx(),p.ry()};
    _oldPos = p;
    if(_edited != nullptr){
       auto rect = _edited->_perimetre;
       traitementEdited();
       if(_edited == nullptr){
           update(rect);
       }
    }
}

template<typename T>
double hypothenuse(T cx, T cy , T mx, T  my){
    auto distx = (mx-cx);
    auto disty = (my-cy);
    return sqrt(distx*distx + disty*disty);
}

void DrGantt::syncGrabState(QPoint &po){
    if(_edited->_perimetre.contains(po)){
        _hovered = _edited;
        if(_edited->_zones._pend.contains(po)){
            _grabbed = GRAB_R;
            this->setCursor(QCursor(_style._curseurEdge));
        }else if(_edited->_zones._pstart.contains(po)){
            _grabbed = GRAB_L;
            this->setCursor(QCursor(_style._curseurEdge));
        }else
            //            (_edited->_zones._pMoveH.contains(po))
        {
            _grabbed = GRAB_MH;
            this->setCursor(QCursor(_style._curseurMoveH));
        }
        //        else{
        //            _grabbed = GRAB_MV;
        //            this->setCursor(QCursor(_style._curseurMoveV));
        //        }
    }else{
        _grabbed = GRAB_NON;
        this->setCursor(QCursor(_style._curseurBase));
    }
}

//methode atteinte lorsqu'un bouton est pressé au lieu du hover
void DrGantt::mouseMoveEvent(QMouseEvent *ev){
    auto po = ev->pos();
    if(_deplacement){
        QPointF prelb = {
            (po.x()-x())/width(),
            (po.y()-y())/height()
        };
        auto rco0 = _model.getCoordsRel(prelb);
//        qInfo()<<rco0;
        //        qInfo()<< "coord rel " <<cx << " " << cy;
        auto dx =  _pointAvant.x()-po.x() ;
        auto dy = _pointAvant.y()-po.y() ;
        //        qInfo()<< "deplacement " << dx << " " << dy;
        _model.deplacement(_model,dx,dy);
        _pointAvant = {po.x(),po.y()};
        retailleVue();
        _makedirty = true;
        update();
        return;
    }
    auto l =  _model.nouvelleLigne(po.y());
    if(l<0)l=0;
    else if(  l >= _model.nbLignes())l=_model.nbLignes()-1;
    _hovered=nullptr;
    if(!_edited)return;
    //    if(_drag_V ){
    //        auto inx = _model.idToIndex(l);

    //            _edited->_data._id = inx;
    //            auto nvis = _model.data2DataModel({l,_edited->_data});
    //            _edited->_zones = nvis._zones;
    //            _edited->_perimetre = nvis._perimetre;
    //            update();
    //        return;
    //    }
    //    else
    if( _drag_H){
        auto np =  _model.nouvellePosition(po.x()) ;   //pas la peine de borner car verif apres
        auto diff = np - _oldPosX;
        if(_edited->_datax._data._end +diff >_model.getLength()){
            auto len = _edited->_datax._data._end -  _edited->_datax._data._start;
            _edited->_datax._data._start = _model.getLength() - len;
            _edited->_datax._data._end = _model.getLength();
        }
        else if(_edited->_datax._data._start +diff <0.0 ){
            auto len = _edited->_datax._data._end -  _edited->_datax._data._start;
            _edited->_datax._data._end =  len;
            _edited->_datax._data._start = 0.0;
        }
        else{
            _edited->_datax._data._start += diff;
            _edited->_datax._data._end += diff;
        }
        auto nvis = _model.data2DataModel(_edited->_datax);
        _edited->_datax._inx = l;
        _edited->_zones = nvis._zones;
        _edited->_perimetre = nvis._perimetre;
        _edited->_datax._data._id= _model.index2Id(l);
        _oldPosX = np;
        update();
        return;
    }
    else if( _extend_HL){
        auto nlen = _edited->_datax._data._end - _model.nouvellePositionBornee(po.x()) ;
        nlen = nlen<0.0 ? 0.0 :nlen;
        _edited->_datax._data._start =  _edited->_datax._data._end -  nlen;
        auto nvis = _model.data2DataModel(_edited->_datax);
        _edited->_zones = nvis._zones;
        _edited->_perimetre = nvis._perimetre;
        update();
        return;
    }
    else if( _extend_HR){
        auto nlen =  _model.nouvellePositionBornee(po.x()) ;
        if(nlen<_edited->_datax._data._start){
            _edited->_datax._data._end =  _edited->_datax._data._start;
        }else{
            _edited->_datax._data._end =  nlen  ;
        }
        auto nvis = _model.data2DataModel(_edited->_datax);
        _edited->_zones    = nvis._zones;
        _edited->_perimetre = nvis._perimetre;
        update();
        return;
    }
}

void DrGantt::hoverMoveEvent(QHoverEvent *ev){
    auto po = ev->pos();
    if(_edited != nullptr){
        syncGrabState(po);
        return;
    }
    auto nseg = selectSegment(po);
    if(nseg != nullptr){
        if( _hovered!=nseg ){
            if(_hovered != nullptr){
                auto rec= _hovered->_perimetre;
                update(rec);
            }
            _hovered = nseg;
            update(_hovered->_perimetre);
        }
    }else if (_hovered != nullptr && nseg == nullptr){
        auto rec= _hovered->_perimetre;
        _hovered = nullptr;
        update(rec);
    }
    if(_makedirty){
        update();
        _makedirty = false;
    }
}
QPointF DrGantt::getCoords(const QPoint& p){
    return {
        QPointF{
            _model.nouvellePosition(p.x()),
                    _model.nouvelleLigne_d(p.y())
        }
    };
}

void DrGantt::wheelEvent(QWheelEvent *me){

    auto pos = me->pos();
    QPointF prelb = {
        (pos.x()-x())/width(),
        (pos.y()-y())/height()
    };
    auto rco0 = _model.getCoordsRel(prelb);
    if(me->angleDelta().y() > 0){
        _model.zoom(0.2);
    }else{
        _model.zoom(-0.2);
    }
    auto rco1 = _model.getCoordsRel(prelb);
    auto diffcoo = rco0-rco1;
    _model.bougeRel(diffcoo);
    retailleVue();
    _makedirty = true;
    update();
}
void DrGantt::mouseDoubleClickEvent(QMouseEvent *me){
    auto p = getCoords(me->pos());
    if(
            p.x()>=0.0 &&
            p.x()<_model.getLength() &&
            p.y()>=0.0  &&
            p.y()<_model.nbLignes()
            ){
        GantDataIndexe*  created =_model.insertion(p.x(),p.y());
        if(created != nullptr){
            auto vd = _model.data2DataModel(*created);
            _vdatas.push_back(vd);
            VueData& pt  = _vdatas.back();
            _edited = &pt;
            _drag_H=false;
            _drag_V=false;
            _extend_HL=false;
            _extend_HR = true;
            update(pt._perimetre);
        }
    }else{
        qInfo()<< "NOT CREATED" << p.x() << " " << p.y();
    }
}


//selectionner un bord ou un segment
void DrGantt::mousePressEvent(QMouseEvent *me)
{
    if(_deplacement)return;
    auto po = me->pos();
    if(me->button() == Qt::RightButton){
        auto cx = po.x();
        auto cy = po.y();
        _pointAvant = {cx,cy};
//        qInfo()<< "coord rel " <<cx << " " << cy;
        _deplacement = true;
        return;
    }
    _hovered = nullptr;
    if(me->button() == Qt::RightButton){
        if(_edited != nullptr){
            auto rec = _edited->_perimetre;
            _edited = nullptr;
            update(rec);
        }
    }else if(me->button() == Qt::LeftButton){
        //je force a selectionner avant de modifier
        if(_edited != nullptr && _edited->_perimetre.contains(po)){
            switch(_grabbed){
            case GRAB_L :{
                _extend_HL = true;
                break;}
            case GRAB_R :{
                _extend_HR = true;
                break;}
                //                case GRAB_MV :{
                //                    _drag_V = true;
                //                    break;}
            case GRAB_MH :{
                _drag_H = true;
                _oldPosX =  _model.nouvellePosition(po.x()) ;
                break;}
            default : break;
            }
            return;
        }
        auto nseg = selectSegment(po);
        if(_edited != nullptr && nseg != _edited){
            QRect rec = _edited->_perimetre;
            _edited = nullptr;
            update(rec);
        }
        _edited = nseg;
        if(_edited != nullptr){
            update(_edited->_perimetre);
        }
    }
}

void DrGantt::retailleVue(){
    _edited = nullptr;
    _hovered =nullptr;
    _model.syncDims((int)width(),(int)height());
    _model.syncGrid(_vgrid);
    syncSelection();
}

void DrGantt::geometryChanged(const QRectF &, const QRectF &){
    retailleVue();
}

//cherche un segment dans le conteneur local
VueData *  DrGantt::selectSegment(QPoint p){
    VueData * ret(nullptr);
    for(VueData &t :  _vdatas){
        if(t._perimetre.contains(p)){
            ret = &t;
        }
    }
    return ret;
}

void DrGantt::suiviCurseur(QMouseEvent *me){
//    qInfo()<<me->pos();
//    qInfo()<<_oldPos;
    _oldPos = me->pos();
}

void DrGantt::syncSelection(){
    _model.syncSelection();
    _vdatas.clear();
    for( auto& da : _model.selection()){
        auto r = _model.data2DataModel(da);
        _vdatas.push_back(r);
    }
}

void DrGantt::paint(QPainter *pntr){
    //    for(DrGanttTrack &z : _tracks){
    //        z.paint(*this,pntr);
    //    }
    //    qInfo()<< "paint: ";
    pntr->setRenderHint(QPainter::Antialiasing, true);
    pntr->fillRect(QRect(0,0,width(),height()),_style._c_fond);
    //    qInfo()<< "selection: " << _visibles.size();
    paintGrid(pntr);
    for(VueData &da : _vdatas){
        if(&da !=_edited ){
            pntr->fillRect(da._perimetre,_style._c_data);
            pntr->setPen(QPen(_style._c_data_tour));
            pntr->drawRect(da._perimetre);
        }
    }
    if(nullptr != _hovered && _hovered != _edited){
        pntr->fillRect(_hovered->_perimetre,_style._c_hovered);
        pntr->setPen(QPen(_style._c_data_tour));
        pntr->drawRect(_hovered->_perimetre);
    }
    if(nullptr != _edited){
        pntr->fillRect(_edited->_perimetre,_style._c_edited);
        pntr->setPen(QPen(_style._c_data_tour));
        pntr->drawRect(_edited->_perimetre);
    }
}


void DrGantt::paintGrid(QPainter *pnt){
    pnt->setPen(_style._c_grid_base);
    pnt->drawLines(_vgrid._H_Lignes);
    pnt->drawLines(_vgrid._V_bases);
    pnt->drawLines(_vgrid._V_metas);
    pnt->drawLines(_vgrid._V_subs);
}

void DrGantt::suppressionEdited(){
    if(_edited == nullptr)return;
    const auto& vd = *_edited;
    const auto& dtr = vd._datax;
    _vdatas.remove(vd);
    _model.suppression(dtr);
    _edited = nullptr;
}

void DrGantt::traitementEdited(){
    //si la duree est 0 je l'elimine
    if(_edited == nullptr)return;
    const auto& vd = *_edited;
    if( vd._datax._data._start == vd._datax._data._end){
        suppressionEdited();
    }
}
