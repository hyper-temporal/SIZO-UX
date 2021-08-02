#ifndef ONDEGRAPHPALETTE_H
#define ONDEGRAPHPALETTE_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QMimeData>
#include <QBitmap>
#include <QDrag>
#include <QApplication> //startDragDistance

class OndeGrapheRessource
        : public QGraphicsItem
{
public:
    OndeGrapheRessource();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QColor color;
};


#endif // ONDEGRAPHPALETTE_H
