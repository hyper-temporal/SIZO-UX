#ifndef DRGRAPHE_H
#define DRGRAPHE_H

#include <QPointF>
#include <QCursor>
#include <QLayout>
#include <QQuickPaintedItem>
#include <QGraphicsItem>
#include "treestyle.h"
#include "drgraphview.h"
#include "drgraphscene.h"
#include "drgraphitempart.h"
#include "jeudetest.h"
#include <logger.h>

class DrGraphe
        :public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY( Qt::CursorShape  curseurDeplacement     READ    getCrDeplacement    WRITE setCrDeplacement )
    Q_PROPERTY( Qt::CursorShape  curseurGrabInput       READ    getCrGrabInput      WRITE setCrGrabInput   )
    Q_PROPERTY( Qt::CursorShape  curseurPlugOutput      READ    getCrPlugOutput     WRITE setCrPlugOutput  )
    Q_PROPERTY( Qt::CursorShape  curseurVide            READ    getCrVide           WRITE setCrVide        )

    Q_PROPERTY( QColor  c_connection  READ    get_c_connection   WRITE set_c_connection     )
    Q_PROPERTY( QColor  c_fond        READ    get_c_fond         WRITE set_c_fond           )
    Q_PROPERTY( QColor  c_data_tour   READ    get_c_tour_bloc    WRITE set_c_tour_bloc      )
    Q_PROPERTY( QColor  c_centre      READ    get_c_centre       WRITE set_c_centre         )
    Q_PROPERTY( int fontsize   READ    getFontSize      WRITE setFontSize     )

    Q_PROPERTY( bool    hoveredAccepted    READ         getHoveredAccepted   WRITE setHoveredAccepted )
public:
    DrGraphe(
            QQuickItem *p=nullptr);
    virtual ~DrGraphe();
    Q_INVOKABLE void addCentreX(double v);
    Q_INVOKABLE void addCentreY(double v);
    Q_INVOKABLE void zoom(double v);
    Q_INVOKABLE void deleteSelection();

    void setModel(const GraphModel& num);
    void setViseur(double v);
    double getViseur()const;
    void setFontSize(int v);
    int getFontSize()const;
    bool getHoveredAccepted();
    void setHoveredAccepted(bool v);
    Qt::CursorShape getCrVide       ()  {return _scene->style()._crVide;}
    Qt::CursorShape getCrDeplacement()  {return _scene->style()._crDeplacement;}
    Qt::CursorShape getCrGrabInput  ()  {return _scene->style()._crGrabInput;}
    Qt::CursorShape getCrPlugOutput ()  {return _scene->style()._crPlugOutput;}
    void setCrVide       (Qt::CursorShape cu){_scene->style()._crVide = cu;}
    void setCrDeplacement(Qt::CursorShape cu){_scene->style()._crDeplacement = cu;}
    void setCrGrabInput  (Qt::CursorShape cu){_scene->style()._crGrabInput= cu;}
    void setCrPlugOutput (Qt::CursorShape cu){_scene->style()._crPlugOutput= cu;}
    void    set_c_centre        (QColor sty){_scene->style()._c_centre = sty;}
    void    set_c_fond          (QColor sty){_scene->style()._c_fond = sty;}
    void    set_c_tour_bloc     (QColor sty){_scene->style()._c_tourBloc = sty;}
    void    set_c_connection    (QColor sty){_scene->style()._c_connection = sty;}
    QColor  get_c_centre        ()const{return _scene->style()._c_centre;}
    QColor  get_c_fond          ()const{return _scene->style()._c_fond;}
    QColor  get_c_tour_bloc     ()const{return _scene->style()._c_tourBloc;}
    QColor  get_c_connection    ()const{return _scene->style()._c_connection;}

public slots:
    void onCreateConnection(){throw "not implemented";}
    void onDeleteConnection(){throw "not implemented";}
    void onCreateRessource(){throw "not implemented";}
    void onDeleteRessource(){throw "not implemented";}
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    void hoverMoveEvent(QHoverEvent *event);
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);
private:
    void paint(QPainter *);
    QGraphicsItem * getPlugOrDrag(QPoint &pos);
    DrGraphView *_vue;
    DrGraphScene * _scene;
    GraphModel _model;

    bool _hoveredAccepted;
    double _cursorSize;
    bool _moving;
    QPointF _pastPoint;
    QPointF _centre;

    QGraphicsLineItem *_line;
    QGraphicsEllipseItem _ghostcursor;

    GraphBlockOutput * _output;
    bool _connecting;

    std::list<QGraphicsItem *> _selected;
};


#endif
