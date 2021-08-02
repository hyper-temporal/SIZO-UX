#ifndef DRFADER_H
#define DRFADER_H


#include <QtQuick/QQuickPaintedItem>
#include "drvaleur.h"

class DrFader
        :public DrValeur
{
Q_OBJECT
    Q_PROPERTY( QColor      fond            READ getfond            WRITE setfond           )
    Q_PROPERTY( QColor      light           READ getlight           WRITE setlight          )
    Q_PROPERTY( QColor      repere          READ getrepere          WRITE setrepere          )
    Q_PROPERTY( bool        horiz           READ gethoriz           WRITE sethoriz          )
    Q_PROPERTY( double      min             READ getmin             WRITE setmin      )
    Q_PROPERTY( double      max             READ getmax             WRITE setmax      )
    void ResizeOrNot();
public:
    DrFader(QQuickItem *p=nullptr);
    virtual ~DrFader();
    void paint(QPainter *)final;
    Q_INVOKABLE void syncParams();
    Q_INVOKABLE void setValeur(double v)final;
//getterSetters
    QColor getrepere  ()  {return _repere     ;}  void setrepere      (QColor v){_repere        =v;}
    QColor getfond    ()  {return _fond       ;}  void setfond        (QColor v){_fond          =v;}
    QColor getlight   ()  {return _light      ;}  void setlight       (QColor v){_light         =v;}
    bool gethoriz   ()  {return _horiz      ;}  void sethoriz       (bool v){_horiz         =v;}
    double getmin()       {return _min        ;}  void setmin         (double v){_min           =v;}
    double getmax()       {return _max        ;}  void setmax         (double v){_max           =v;}
protected:
    void coord2Value(int mx, int my)final;
private:
    QColor _fond;
    QColor _light;
    QColor _repere;
    bool _horiz;
    double _min,_max;

    double _rmin,_rmax;
    double _dist;
    bool _changementdesigne ,_sensinverse ;
    double _rel0;
    double _valrel;

};
#endif // DRFADER_H
