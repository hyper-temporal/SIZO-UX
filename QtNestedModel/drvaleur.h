#ifndef DRVALEUR_H
#define DRVALEUR_H

#include <QQuickPaintedItem>


class DrValeur
        :public QQuickPaintedItem
{
Q_OBJECT
    Q_PROPERTY(double val READ getval WRITE setval  )
public:
    DrValeur(QQuickItem *p=nullptr);
    virtual ~DrValeur();
    double getval(){return _value;}
    void setval(double v){setValeur(v);}
protected slots:
    void mousePressEvent(QMouseEvent *me);
    void mouseMoveEvent(QMouseEvent *me);
    void mouseReleaseEvent(QMouseEvent *);
protected:
    virtual void coord2Value(int mx, int my)=0;
    virtual void setValeur(double v)=0;
protected:
    double _value;
    bool _isdragging;
};

#endif // DRVALEUR_H
