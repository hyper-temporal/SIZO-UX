#ifndef VUEGRAPH_H
#define VUEGRAPH_H

#include <QGraphicsView>

//classe créée uniquement pour permettre l'acces aux evenements
class DrGraphView
        :public QGraphicsView
{
public:
    virtual ~DrGraphView();
    DrGraphView(QGraphicsScene *scene);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void setZoom(double v);
    void deplacerX(double v);
    void deplacerY(double v);
    void deplacerXY(double dx,double dy);
    const QRectF bornesVisibles()const;
private:

};

#endif // VUEGRAPH_H
