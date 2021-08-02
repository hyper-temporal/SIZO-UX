#ifndef DRONDE_H
#define DRONDE_H

#include "drshape.h"

class DrOnde1D
        :public DrShape
{
Q_OBJECT
    Q_PROPERTY( bool    looped    READ  getlooped     WRITE setlooped   )
    Q_PROPERTY( int     interpoltype    READ  getinterpolation     WRITE setinterpolation   )
    int _cind ;
public:
    DrOnde1D(QQuickItem *p=nullptr);
    virtual ~DrOnde1D();
    void mouseReleaseEvent(QMouseEvent *);
private:
    void paintEnveloppe(QPainter&painter, std::vector<data2D> &datas)final;
    void setinterpolation(int sty){_style._interpolation = sty;}
    int getinterpolation()const{return _style._interpolation;}
    void setlooped(bool sty){_style._looped = sty;}
    bool getlooped()const{return _style._looped;}

    void suiviCurseur(QMouseEvent *me);
    void relachement();
    void linearMorphing(int from, int to);

    int getSampleNumber(QMouseEvent *me);
};





#endif // DRONDE_H
