#ifndef QCKENVELOPPE_H
#define QCKENVELOPPE_H


#include "drshape.h"

class DrGanttOptim
        :public DrShape
{
Q_OBJECT
public:
    DrGanttOptim(QQuickItem *p=nullptr);
    virtual ~DrGanttOptim();
private slots:
    void mousePressEvent(QMouseEvent *me)final;
    void mouseReleaseEvent(QMouseEvent *me)final;
private:
    void paintEnveloppe(QPainter&painter, std::vector<data2D> &datas)final;
    void suiviCurseur(QMouseEvent *me);
    int getSampleNumber(QMouseEvent *me)final;
};




#endif // QCKENVELOPPE_H
