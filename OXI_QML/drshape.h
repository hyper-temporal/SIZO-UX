#ifndef DRSHAPE_H
#define DRSHAPE_H

#include <QQuickPaintedItem>
#include <boio.h>

enum TypeInterpolation
{
    INTERPOLATION_NONE = 0,
    INTERPOLATION_LINEAR = 1,
    INTERPOLATION_HERMITE = 2,
};

struct StyleCourbe{
    QColor
    _fond,
    _bord,
    _fondhaut,
    _fondBas,
    _centre,
    _courbe,
    _points;
    int _interpolation;
    bool _looped;
};


static std::vector<data2D> testvec()
{
    return  {
        {0.0,0.0},
        {0.25,-1.0},
        {0.5,0.5},
        {0.75,0.25},
        {1.0,1.0},
    };

}

class DrShape
        :public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY( QColor  fond      READ  getfond       WRITE setfond     )
    Q_PROPERTY( QColor  bord      READ  getbord       WRITE setbord     )
    Q_PROPERTY( QColor  fondhaut  READ  getfondhaut   WRITE setfondhaut )
    Q_PROPERTY( QColor  fondBas   READ  getfondBas    WRITE setfondBas  )
    Q_PROPERTY( QColor  centre    READ  getcentre     WRITE setcentre   )
    Q_PROPERTY( QColor  courbe    READ  getcourbe     WRITE setcourbe   )
    Q_PROPERTY( QColor  points    READ  getpoints     WRITE setpoints   )
    Q_PROPERTY( int     pixmax    READ  getpixmax     WRITE setpixmax  )

    Q_INVOKABLE void setData(std::vector<data2D>);

public:
    DrShape(QQuickItem *p=nullptr);
    virtual ~DrShape();

    void setfond(QColor sty){_style._fond = sty;}
    QColor getfond()const{return _style._fond;}
    void setbord(QColor sty){_style._bord = sty;}
    QColor getbord()const{return _style._bord;}
    void setfondhaut(QColor sty){_style._fondhaut = sty;}
    QColor getfondhaut()const{return _style._fondhaut;}
    void setfondBas(QColor sty){_style._fondBas = sty;}
    QColor getfondBas()const{return _style._fondBas;}
    void setcentre(QColor sty){_style._centre = sty;}
    QColor getcentre()const{return _style._centre;}
    void setcourbe(QColor sty){_style._courbe = sty;}
    QColor getcourbe()const{return _style._courbe;}
    void setpoints(QColor sty){_style._points = sty;}
    QColor getpoints()const{return _style._points;}
    void setpixmax(int v){_pixmax = v;}
    int getpixmax()const{return _pixmax;}
    void paint(QPainter *);

protected:
    void paintDomainClassic(QPainter&painter, std::vector<data2D> &datas);
    void paintInterpolationHermite( QPainter&painter, std::vector<data2D> &datas);
    virtual void paintEnveloppe(QPainter&painter,  std::vector<data2D> &datas)=0;

protected slots:
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);
    virtual void mouseReleaseEvent(QMouseEvent *);
protected:
    virtual int getSampleNumber(QMouseEvent *me)=0;
    virtual void suiviCurseur(QMouseEvent *me)=0;
protected:
    std::vector<data2D> _datas;
    StyleCourbe _style;
    int _pixmax;
    int _pointSelected;
};


#endif // DRSHAPE_H
