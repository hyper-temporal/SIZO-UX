#ifndef DRGRAPHCURSOR_H
#define DRGRAPHCURSOR_H


#include <QGraphicsItem>

class DrGraphCursor
        :public QGraphicsItem

{
public:
    DrGraphCursor(QGraphicsItem *parent = nullptr);
    void setPressed(bool);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
private:
    bool _ispressed;
    QGraphicsEllipseItem _ellipse;
    QGraphicsLineItem _lineV,_lineH;

};

#endif // DRGRAPHCURSOR_H
