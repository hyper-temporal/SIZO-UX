#include "drgraphconnection.h"
#include <math.h>
#include <QPen>
#include <QPainter>

DrGraphConnection::~DrGraphConnection(){
//    _output = nullptr;
//    _input = nullptr;
}

DrGraphConnection::DrGraphConnection(
        GraphBlockOutput *startItem,
        GraphBlockInput *endItem,
        QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
    ,_selected(false)
    ,_output(startItem)
    ,_input(endItem)
    ,_color(QColor(80,80,200))
    ,_colorSelected(QColor(200,50,50))
    ,_q({startItem->query(),endItem->query()})
{
//    setFlag(QGraphicsItem::ItemIsSelectable, true);
//    setFlag(QGraphicsItem::ItemIsMovable, true);
}

QRectF DrGraphConnection::boundingRect() const
{
//    return QRectF(0,0,0,0);

    return QRectF(_output->sceneBoundingRect().center(),
                  _input->sceneBoundingRect().center())
        .normalized()
            .adjusted(10,10,10,10)
            ;
}

#include <QDebug>
void DrGraphConnection::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *o,
          QWidget *w)
{
    Q_UNUSED(o);
    Q_UNUSED(w);

    auto ligne = QLineF(_output->sceneBoundingRect().center(),
                    _input->sceneBoundingRect().center());
    painter->setPen(QPen(_selected?_colorSelected:_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    setLine(ligne);
    painter->drawLine(line());

}
