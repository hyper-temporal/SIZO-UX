#include "drgraphcursor.h"

DrGraphCursor::DrGraphCursor(QGraphicsItem *p)
    :QGraphicsItem(p)
    ,_ellipse(this)
   , _lineH(this)
    ,_lineV(this)
{
    auto lv = QLineF({0,-1},{0,1});
    auto lh = QLineF({-1,0},{1,0});
    _lineV.setLine(lv);
    _lineH.setLine(lh);
}


void DrGraphCursor::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    (void)option;
    (void)widget;

    _ellipse.paint(painter,option,widget);
    _lineV.paint(painter,option,widget);
    _lineH.paint(painter,option,widget);
}

void DrGraphCursor::setPressed(bool st){
    _ispressed = st;
    if(_ispressed){
        _ellipse.setRect(-3,-3,6,6);
    }else{
        _ellipse.setRect(-5,-5,10,10);
    }

}

QRectF DrGraphCursor::boundingRect()const {
    return _ellipse.rect();
}

//QRect DrGraphCursor::rect(){
//    return QGraphicsItem::boundingRect();
//}
