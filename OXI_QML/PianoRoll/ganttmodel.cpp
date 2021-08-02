#include "ganttmodel.h"
#include <QDebug>

static std::vector<int> lignes = {
    0,1,2,3,4,12,64
};

static std::list<NodeInput> datatest(){
    std::list<NodeInput> ret;
    srand(1234);
    for(uint i(0);i<128;i++){
        std::list<NodeInput> lret(20);
        for(NodeInput &el : lret){
            el._start = 12.0*(double)rand()/INT32_MAX;
            auto len  = (double)rand()/INT32_MAX;
            el._end = el._start + len;
            el._id =i;
        }

//        for(int j(0); j<20; j++){
//            auto el = new NodeInput();
//            el->_start = 12.0*(double)rand()/INT32_MAX;
//            auto len  = (double)rand()/INT32_MAX;
//            el->_end = el->_start + len;
//            el->_id = j;
//            lret.push_back(*el);
//        }
        ret.insert(ret.end(),lret.begin(),lret.end());
    }
    return ret;
}

static GridModel gridpardefaut=
{
    4,      // div*x
    4,      // div/x
    3,      // div relative
    0.0,    //valeur absolue ignorée si vrai
};

GanttModel::GanttModel()
    :_pix_par_ligne(0)
    ,_s_par_pix(0.0)
    ,_vX(0.0)
    ,_vY(0.0)
    ,_tmin(0.0)
    ,_lmin(0.0)
    ,_grid(gridpardefaut)
    ,_datas(datatest())
    ,_L_Id(lignes)
{

}

GanttModel::~GanttModel(){
}


double GanttModel::getLength()const{
    return _dureeTotale;
}
void GanttModel::setDuree(double v){
    _dureeTotale = v;
}


double GanttModel::getSparPix()const {
    return _s_par_pix;
}
void GanttModel::setsecondeParPixel(double v){
    _s_par_pix = v>0?v:0.01;
    _zoneminH = 4; //eventuellment contextuel / proportionel
    _gWidth =  _dureeTotale/_s_par_pix;
    syncGWidth();
}


void GanttModel::syncGWidth(){
    _rWidth = _width/_gWidth;
    syncH();
}
void GanttModel::syncGHeight(){
    _rHeight = _height/_gHeight;
    syncV();
}
double GanttModel::getpixperline()const {
    return _pix_par_ligne;
}
void GanttModel::setpixperline(double v){
    _pix_par_ligne = v>1.0?v:1.0;
    _zoneminV = _pix_par_ligne < 2.0 ?
                1 : _pix_par_ligne < 4.0 ?
                    (uint)_pix_par_ligne :4;


    _gHeight = _pix_par_ligne * _L_Id.size();
    syncGHeight();
}

//void GanttModel::setCentreRel(double trel, double lrel){
//    _vX = trel;
//    _vY = lrel;
//}

double GanttModel::nouvelleLigne_d(int y)const{
    return _lmin + (double)(_lmin + y) / _pix_par_ligne;
}


int GanttModel::nouvelleLigne(int y)const{
    return _lmin + (double)(_lmin + y) / _pix_par_ligne;
}

double GanttModel::nouvellePosition(int x)const{
    return _tmin+ (double)x*_s_par_pix;
}
double GanttModel::nouvellePositionBornee(int x)const{
    auto dist = nouvellePosition(x);
    if(dist < 0.0)
        return 0.0;
    else if (dist > _dureeTotale)
        return _dureeTotale;
    else return dist;
}
VueData GanttModel::data2DataModel(GantDataIndexe& data){
    auto &da = data._data;
    int  inx = data._inx;

    double relH = +(inx-_lmin)*_pix_par_ligne ;
    double relG = (da._start-_tmin)/_s_par_pix;
    double relD = -1+(da._end-_tmin)/_s_par_pix;
    auto start = QPoint(relG,relH);
    auto end = QPoint(relD,-1+relH+_pix_par_ligne);
    auto r= QRect(start,end);
    auto rV = r.adjusted(_zoneminH,0,-_zoneminH,0); //reduit des 2 cotés
    auto rH = rV.adjusted(4*_zoneminH,0,4*_zoneminH,0); //reduit encore plus
    auto rG = r;
    rG.setRight(relG+_zoneminH);
    auto rD = r;
    rD.setLeft(relD-_zoneminH);
    return {r,{rV,rH,rG,rD},data};
}


std::list<GantDataIndexe> &GanttModel::selection(){
    return _selection;
}

void GanttModel::syncSelection(){
    _selection.clear();
    if(_lmin>_L_Id.size() || _tmin>_dureeTotale)return;
    for(NodeInput &data : _datas){
        auto inx  =Id2Index(data._id);
        if(
                (data._end >= _tmin   && data._start <= _tmax) &&
                inx>=0
                ){
            _selection.push_back({inx,data});
        }
    }
}


//double GanttModel::getPositionX()const {
//    return _vX;
//}
//double GanttModel::getPositionY()const {
//    return _vY;
//}

void GanttModel::syncDims(int w, int h){
    _width =w;
    _height =h;
    syncGWidth();
    syncGHeight();
}

void GanttModel::syncH(){
    _tmin = _vX * _dureeTotale;
    syncAfterTMin();
}
void GanttModel::syncAfterTMin(){
    _tlen = _rWidth * _dureeTotale;
    _tmax = _tmin + _tlen;
}
void GanttModel::syncV(){
    _lmin = _vY * _L_Id.size() ;
    syncAfterLMin();
}

void GanttModel::syncAfterLMin(){
    _llen = _rHeight * _L_Id.size() ;
    _lmax = _lmin + _llen;
}



void GanttModel::syncGrid(VueGrid &gridm){

    cadreG = (0.0-_tmin)/_s_par_pix;
    cadreD = (_dureeTotale-_tmin)/_s_par_pix;
    cadreH = (0.0-_lmin)*_pix_par_ligne ;
    cadreB = (_L_Id.size()-_lmin)*_pix_par_ligne ;
    //a partir du model je vais selectionner les axes qui seront représentés dans la fenetre de selection
    //simple positionnement relatif entre _vx et _vx+_rwidth
    //= duree/_relative si _relative>0 ou absolue sinon
    double divdebase = _grid._relative>0?1.0/_grid._relative:_grid._absolue;

    auto div_meta   = divdebase * _grid._metagrid;
    auto div_sub    = _grid._subgrid>0? divdebase / _grid._subgrid : 0.0;

    _VAxes.clear();
    _VAxesMeta.clear();
    _VAxesSub.clear();
    _HAxes.clear();

    int baseNb =  (_dureeTotale)    /   (divdebase) ;
    int metaNb =  (_dureeTotale)    /   (div_meta) ;
    int subNb =     (_dureeTotale)  /   (div_sub);

    for(auto i(0); i<baseNb;i++){
        auto val = ((i*divdebase) );
        if(val >= 0.0 &&  val <= 1.0){
            _VAxes.push_back((val- _vX)*_gWidth);
        }
    }
    for(auto i(0); i<metaNb;i++){
        auto val = ((i*div_meta) );
        if(val >= 0.0 &&  val <= 1.0){
            _VAxes.push_back((val- _vX)*_gWidth);
        }
    }
    for(auto i(0); i<subNb;i++){
        auto val = ((i*div_sub) );
        if(val >= 0.0 &&  val <= 1.0){
            _VAxes.push_back((val- _vX)*_gWidth);
        }
    }
    double hdiv = 1.0/_L_Id.size();
    for(uint i(0); i<=_L_Id.size();i++){
        double dist = (i*hdiv) - _vY ;
        _HAxes.push_back(dist*_gHeight);
    }
    gridm._H_Lignes.clear();
    gridm._V_bases.clear();
    gridm._V_metas.clear();
    gridm._V_subs.clear();

    for( auto &da : VAxes()){
        auto r = QLine({da,cadreH},{da,cadreB});
        gridm._V_bases.push_back(r);
    }
    for( auto &da : HAxes()){
        auto r = QLine({cadreG,da}, {cadreD,da});
        gridm._H_Lignes.push_back(r);
    }
}

int GanttModel::Id2Index(int l){
    for(uint cnt(0);cnt<_L_Id.size();cnt++){
        if(_L_Id[cnt] == l){
            return cnt;
        }
    }
    return -1;
}
int GanttModel::index2Id(int index){
    if(index >=0 && index < (int)_L_Id.size() ){
        return _L_Id[index];
    }
    return -1;
}

bool GanttModel::idEstPresent(int id){
    for(auto i : _L_Id){
        if(i==id)
            return true;
    }
    return false;
}



void GanttModel::zoom(double v){
    double ratio = _gWidth/_gHeight;
    auto fpix = _pix_par_ligne + v*_pix_par_ligne;
    _pix_par_ligne = fpix;
    _s_par_pix = _dureeTotale/(ratio*_pix_par_ligne*_L_Id.size());
    _gHeight = _pix_par_ligne * _L_Id.size();
    _gWidth =  _dureeTotale/_s_par_pix;
    syncGHeight();
    syncGWidth();

    qInfo()<< _vX;
    qInfo()<< _vY;
}
void GanttModel::deplacement(
        GanttModel& m ,
        double dx,
        double dy){
    m._vX += (( dx / m._gWidth ));
    m._vY += (( dy / m._gHeight));
    qInfo()<< m._vX;
    qInfo()<< m._vY;
}


const double minimumlength = 0.001;

GantDataIndexe* GanttModel::insertion(double x, double y){
    int inx = y;
    int id = index2Id(inx);
    if(id >=0){
        _datas.push_back({x,x,id});
        auto& nd = _datas.back();
        _selection.push_back({inx,nd});
        return &(_selection.back());
    }
    return nullptr;
 }

void GanttModel::suppression(const GantDataIndexe& node){
    const auto& data = node._data;
    _selection.remove(node);
    _datas.remove(data);
}

void GanttModel::addCentreX(double v){
    _vX+= v*_tlen;
}

void GanttModel::addCentreY(double v){
    _vY+= v*_llen;
}

QPointF GanttModel::getCoordsRel(QPointF& p){
    return {_vX+ _rWidth*p.x(),_vY +_rHeight*p.y()};
}

void GanttModel::bougeRel(QPointF& p){
    _vX += p.x();
    _vY += p.y();
}

QPointF GanttModel::getCoordsCentre(){
    return {_vX+_rWidth/2,_vY+_rHeight/2};
}
void GanttModel::setCoordsCentre(QPointF& c){
    auto oc = getCoordsCentre();
    auto dx = c.x()-oc.x();
    auto dy = c.y()-oc.y();
    _vX+=dx;
    _vY+=dy;
}

