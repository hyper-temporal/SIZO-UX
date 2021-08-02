#ifndef DRGANTT_H
#define DRGANTT_H

#include <QCursor>
#include <QQuickPaintedItem>
#include <cmath>
#include <list>
#include "ganttmodel.h"

struct StyleGanttTracks{
    Qt::CursorShape
    _curseurMoveV,
    _curseurMoveH,
    _curseurEdge,
    _curseurBase;
    QColor
    _c_data,
    _c_hovered,
    _c_edited,
    _c_fond,
    _c_bord,
    _c_data_tour,
    _c_grid_meta,
    _c_grid_sub,
    _c_grid_base;
    int _interpolation;
    bool _looped;
};

class DrGanttVue:
        public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY( bool  hoveredAccepted        READ    getHoveredAccepted         WRITE setHoveredAccepted     NOTIFY  hoveredAcceptedChanged       )
    Q_PROPERTY( Qt::CursorShape  curseurMoveV        READ    getCurseurMoveV         WRITE setCurseurMoveV           )
    Q_PROPERTY( Qt::CursorShape  curseurMoveH        READ    getCurseurMoveH         WRITE setCurseurMoveH           )
    Q_PROPERTY( Qt::CursorShape  curseurEdge        READ    getCurseurEdge         WRITE setCurseurEdge           )
    Q_PROPERTY( Qt::CursorShape  curseurBase        READ    getCurseurBase         WRITE setCurseurBase          )

    Q_PROPERTY( QColor  c_grid_base     READ    get_c_grid_base        WRITE set_c_grid_base           )
    Q_PROPERTY( QColor  c_grid_meta     READ    get_c_grid_meta        WRITE set_c_grid_meta           )
    Q_PROPERTY( QColor  c_grid_sub      READ    get_c_grid_sub         WRITE set_c_grid_sub            )
    Q_PROPERTY( QColor  c_hovered        READ    get_c_hovered         WRITE set_c_hovered           )
    Q_PROPERTY( QColor  c_data        READ    get_c_data         WRITE set_c_data           )
    Q_PROPERTY( QColor  c_edited        READ    get_c_edited()         WRITE set_c_edited           )
    Q_PROPERTY( QColor  c_fond        READ    get_c_fond         WRITE set_c_fond           )
    Q_PROPERTY( QColor  c_data_tour      READ    get_c_data_tour       WRITE set_c_data_tour         )

public:
    DrGanttVue(QQuickItem *p=nullptr);
    bool getHoveredAccepted(){
        return _hoveredAccepted;
    }
    void setHoveredAccepted(bool v){
        _hoveredAccepted = v;
        setAcceptHoverEvents(_hoveredAccepted);
    }

    Qt::CursorShape getCurseurMoveH(){return _style._curseurMoveH;}
    Qt::CursorShape getCurseurMoveV(){return _style._curseurMoveV;}
    Qt::CursorShape getCurseurEdge(){return _style._curseurEdge;}
    Qt::CursorShape getCurseurBase(){return _style._curseurBase;}
    void setCurseurMoveH(Qt::CursorShape cu){_style._curseurMoveH = cu;}
    void setCurseurMoveV(Qt::CursorShape cu){_style._curseurMoveV = cu;}
    void setCurseurEdge(Qt::CursorShape cu){_style._curseurEdge = cu;}
    void setCurseurBase(Qt::CursorShape cu){_style._curseurBase = cu;}
    void    set_c_grid_base (QColor sty){_style._c_grid_base = sty;}
    void    set_c_grid_meta (QColor sty){_style._c_grid_meta = sty;}
    void    set_c_grid_sub  (QColor sty){_style._c_grid_sub = sty;}
    void    set_c_hovered   (QColor sty){_style._c_hovered = sty;}
    void    set_c_edited    (QColor sty){_style._c_edited = sty;}
    void    set_c_data      (QColor sty){_style._c_data = sty;}
    void    set_c_fond(QColor sty){_style._c_fond = sty;}
    void    set_c_data_tour(QColor sty){_style._c_data_tour = sty;}
    void    setpoints(QColor sty){_style._c_grid_base = sty;}
    QColor  get_c_grid_base ()const{return _style._c_grid_base;}
    QColor  get_c_grid_meta ()const{return _style._c_grid_meta;}
    QColor  get_c_grid_sub  ()const{return _style._c_grid_sub;}
    QColor  get_c_hovered()const{return _style._c_hovered;}
    QColor  get_c_edited()const{return _style._c_edited;}
    QColor  get_c_data()const{return _style._c_data;}
    QColor  get_c_fond()const{return _style._c_fond;}
    QColor  get_c_data_tour()const{return _style._c_data_tour;}


signals:
    void hoveredSegmentChanged();
    void hoveredEndChanged();
    void hoveredAcceptedChanged();
protected:
    bool _hoveredAccepted;
    StyleGanttTracks _style;
    GanttModel _model;
};

class DrGantt
        :public DrGanttVue
{
    Q_OBJECT

    Q_PROPERTY( qreal   pixperline          READ    getpixperline   WRITE setpixperline     )
    Q_PROPERTY( qreal   secondeParPixel     READ    getSparPix      WRITE setsecondeParPixel       )
    Q_PROPERTY( qreal   duree               READ    getLength        WRITE setDuree )
public:
    DrGantt(QQuickItem *p=nullptr);
    virtual ~DrGantt();
    double getLength()const;
    void setDuree(double v);
    double getSparPix()const;
    void setsecondeParPixel(double v);
    double getpixperline()const;
    void setpixperline(double v);

    Q_INVOKABLE void addCentreX(double v);
    Q_INVOKABLE void addCentreY(double v);
protected:

    void wheelEvent(QWheelEvent *event)final;
    void mouseDoubleClickEvent(QMouseEvent *me)final;
    void mousePressEvent(QMouseEvent *me)final;
    void mouseReleaseEvent(QMouseEvent *)final;
    void mouseMoveEvent(QMouseEvent *)final;
    void hoverMoveEvent(QHoverEvent *event)final;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)final;
private:
    void actualiseVue();
    void paint(QPainter *);
    void paintGrid(QPainter *);
    void traitementEdited();
    void suppressionEdited();
    QPointF getCoords(const QPoint& p);

    void syncSelection();
    void retailleVue();
    VueData *selectSegment(QPoint me);
    virtual void suiviCurseur(QMouseEvent *me);
    void syncGrabState(QPoint &po);
    std::list<VueData> _vdatas;
    VueData * _edited,* _hovered;
    QPoint _oldPos;
    double _oldPosX;
    bool _drag_V,_drag_H,_extend_HL,_extend_HR;
    DataGrab _grabbed;
    int _editedIndex;
    bool _makedirty;
    VueGrid _vgrid;

    bool _deplacement;
    QPoint _pointAvant;
};


#endif // DRSHAPE_H
