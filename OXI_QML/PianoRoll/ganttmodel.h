#ifndef GANTTMODEL_H
#define GANTTMODEL_H

#include <vector>
#include <list>
#include <QVector>
#include <QLine>
#include "ganttdata.h"
#include <QRect>
#include <cmath>

struct  GridModel{
    uint  _subgrid;             //trait toutes les n divs
    uint  _metagrid;            //n traits par div
    uint _relative;
    double _absolue;
};

struct ZonesActions{
    QRect _pMoveV;
    QRect _pMoveH;
    QRect _pstart;
    QRect _pend;
};

struct VueData{
    QRect _perimetre;
    ZonesActions _zones;
    GantDataIndexe &_datax;
    bool operator ==(const VueData& v){
        return this == &v;
    }
};


struct VueGrid
{
    QVector<QLine> _V_bases;
    QVector<QLine> _V_metas;
    QVector<QLine> _V_subs;
    QVector<QLine> _H_Lignes;
};


class GanttModel
{
public:
    GanttModel();
    virtual ~GanttModel();
    GantDataIndexe *insertion(double x, double y);
    void suppression(const GantDataIndexe &);
    int nbLignes()const{return  _L_Id.size();}
//    virtual void setCentreRel(double trel, double lrel);
    double nouvelleLigne_d(int y)const;
    int nouvelleLigne(int y)const;
    double nouvellePosition(int x)const;
    double nouvellePositionBornee(int x)const;
    VueData data2DataModel(GantDataIndexe &data);
    //creation des geometries
    virtual void syncSelection();
    std::list<GantDataIndexe>& selection();
    void syncDims(int,int);
    double getLength()const ;
    void setDuree(double v);
    double getpixperline()const ;
    void setpixperline(double v);
    double getSparPix()const ;
    void setsecondeParPixel(double v);
    void syncGrid(VueGrid &gridm);
    int Id2Index(int);
    int index2Id(int);
    void zoom(double d);
    void deplacement(GanttModel& m ,double dx, double dy);
    void addCentreX(double v);
    void addCentreY(double v);
    QPointF getCoordsRel(QPointF& p);
    void bougeRel(QPointF& p);
    QPointF getCoordsCentre();
    void setCoordsCentre(QPointF& c);
private:
    std::vector<int>& VAxes()    {    return _VAxes;      }
    std::vector<int>& VAxesMeta(){    return _VAxesMeta;  }
    std::vector<int>& VAxesSub() {    return _VAxesSub;   }
    std::vector<int>& HAxes()    {    return _HAxes;      }

    bool idEstPresent(int id);
    void syncGWidth();
    void syncGHeight();
    void syncH();
    void syncAfterTMin();
    void syncV();
    void syncAfterLMin();
    double _dureeTotale;
    double          //
    _pix_par_ligne,
    _s_par_pix;
    uint _zoneminH,_zoneminV;  //nb pixelmin
    double
    _gWidth         //_dureeTotale * _pixParMs  => en pixel
    ,_gHeight;      //_nbLignes*_pixpLigne
    double _vX,_vY;         //coordonnées de la vue relative au plan global (0.0 en, haut a gauche 1.0 1.0 en bas a droite)
    double                  //definition de la fenetre relativement au plan global
    _rWidth,                //=_width/_gWidth
    _rHeight;               //=_height/_gHeight
    double //correspondances entre vue et donnée
    _tmin,      ///= _vX*_dureeTotale
    _tlen,      ///= _rWidth*_dureeTotale
    _tmax,      ///= _tmin+_tlen
    _lmin,      ///= _vY*_nbLignes*_pixpLigne
    _llen,      ///=_rHeight*_nbLignes*_pixpLigne
    _lmax;      ///= _lmin+_llen
    GridModel _grid;
    std::vector<int> _VAxes;
    std::vector<int> _VAxesMeta;
    std::vector<int> _VAxesSub;
    std::vector<int> _HAxes;
    int cadreG ,cadreD,cadreH,cadreB ;
    int _width,_height;
    std::list<GantDataIndexe> _selection;
    std::list<NodeInput> _datas;
    std::vector<int> _L_Id;
};



#endif // GANTTMODEL_H
