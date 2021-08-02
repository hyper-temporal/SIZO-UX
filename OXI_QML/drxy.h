#ifndef DRXY_H
#define DRXY_H


#include <QtQuick/QQuickPaintedItem>
#include "drvaleur.h"

class DrXY
        :public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY( QColor      fond            READ getfond            WRITE setfond      )
    Q_PROPERTY( QColor      light           READ getlight           WRITE setlight     )
    Q_PROPERTY( QColor      repere          READ getrepere          WRITE setrepere    )
    Q_PROPERTY( double      minX            READ getminX            WRITE setminX      )
    Q_PROPERTY( double      maxX            READ getmaxX            WRITE setmaxX      )
    Q_PROPERTY( double      minY            READ getminY            WRITE setminY      )
    Q_PROPERTY( double      maxY            READ getmaxY            WRITE setmaxY      )
    void ResizeOrNot();
public:
    DrXY(QQuickItem *p=nullptr);
    virtual ~DrXY();
    void paint(QPainter *)final;
    Q_INVOKABLE void syncParams();
    Q_INVOKABLE void setValeurs(double vx, double vy);
//getterSetters
    QColor getrepere  ()  {return _repere     ;}  void setrepere      (QColor v){_repere        =v;}
    QColor getfond    ()  {return _fond       ;}  void setfond        (QColor v){_fond          =v;}
    QColor getlight   ()  {return _light      ;}  void setlight       (QColor v){_light         =v;}
    bool gethoriz   ()  {return _horiz      ;}  void sethoriz       (bool v){_horiz         =v;}
    double getminX    ()  {return _minX       ;}  void setminX        (double v){_minX          =v;}
    double getmaxX    ()  {return _maxX       ;}  void setmaxX        (double v){_maxX          =v;}
    double getminY    ()  {return _minY       ;}  void setminY        (double v){_minY          =v;}
    double getmaxY    ()  {return _maxY       ;}  void setmaxY        (double v){_maxY          =v;}
protected slots:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *);
protected:
    void coord2Values(int mx,int my);
private:
    bool _isdragging;

    QColor _fond;
    QColor _light;
    QColor _repere;
    bool _horiz;
    double _minX,_maxX;
    double _minY,_maxY;

    double _rminX,_rmaxX;
    double _rminY,_rmaxY;
    double _distX,_distY;
    bool _changementdesigneX ,_sensinverseX ;
    bool _changementdesigneY ,_sensinverseY ;
    double _rel0X,_rel0Y;
    double _valrelX;
    double _valrelY;
    double _valX;
    double _valY;

};
#endif // DRXY_H
