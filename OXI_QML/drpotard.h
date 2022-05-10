#ifndef DRPOTARD_H
#define DRPOTARD_H


#include <QtQuick/QQuickPaintedItem>
#include "drvaleur.h"
#include <rotation.h>

class DrPotard
        :public DrValeur
{
Q_OBJECT
    Q_PROPERTY( QColor  fond    READ  getfond       WRITE setfond       )
    Q_PROPERTY( QColor  toursel READ  gettoursel    WRITE settoursel    )
    Q_PROPERTY( QColor  light   READ  getlight      WRITE setlight      )
    Q_PROPERTY( double  centre  READ  getcentre     WRITE setcentre     )
    Q_PROPERTY( double  deadz   READ  getdeadz      WRITE setdeadz      )
    Q_PROPERTY( double  cx      READ  getcx         WRITE setcx         )
    Q_PROPERTY( double  cy      READ  getcx         WRITE setcy         )
    Q_PROPERTY( double  radius  READ  getradius     WRITE setradius     )
    Q_PROPERTY( bool    sens    READ  getsens       WRITE setsens       )
public:
    DrPotard(QQuickItem *p=nullptr);
    virtual ~DrPotard();
    void paint(QPainter *)final;
    Q_INVOKABLE void syncParams();
    Q_INVOKABLE void setValeur(double v)final;
//getterSetters
    QColor getfond    (){return _fond      ;}  void   setfond     (QColor v){_fond      =v;}
    QColor gettoursel (){return _toursel   ;}  void   settoursel  (QColor v){_toursel   =v;}
    QColor getlight   (){return _light     ;}  void   setlight    (QColor v){_light     =v;}
    double getcentre  (){return _centre    ;}  void   setcentre   (double v){_centre    =v;}
    double getdeadz   (){return _deadz     ;}  void   setdeadz    (double v){_deadz     =v;}
    double getsens    (){return _sens      ;}  void   setsens     (double v){_sens      =v;}
    double getcx      (){return _cx        ;}  void   setcx       (double v){_cx        =v;}
    double getcy      (){return _cy        ;}  void   setcy       (double v){_cy        =v;}
    double getradius  (){return _radius    ;}  void   setradius   (double v){_radius    =v;}
protected:
    void coord2Value(int mx, int my)final;
private:
    QColor _fond         ;
    QColor _toursel      ;
    QColor _light        ;
    double _dist, _arclen,_arcstart;
    bool _sens;
    double
    _deadz,// 1.0 reste rien...
    _centre,  // 0.75 => bas
    _cx,_cy,
    _radius;
    double _aL,_aR;
    int _mx,_my;
    bool _resize;
};
#endif // DRPOTARD_H
