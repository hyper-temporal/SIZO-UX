#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include "drgraphitempart.h"


class DrGraphConnection
        :public QGraphicsLineItem
{
    bool _selected;
public:
    virtual ~DrGraphConnection();
    DrGraphConnection(
            GraphBlockOutput *startItem,
            GraphBlockInput *endItem,
      QGraphicsItem *parent = 0);
    int type() const override { return ZCONNECT; }
    QRectF boundingRect() const override;
    void setColor(const QColor &color) { _color = color; }
    GraphBlockOutput *getOutput() const { return _output; }
    GraphBlockInput *getInput() const { return _input; }
    const IOLink*  getQuery()const{
        return &_q;
    }
    bool getSelected()const{ return _selected;}
    void setSelected(bool st){  _selected = st;}
    void inverseSelected( ){  _selected = !_selected;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
private:
    GraphBlockOutput *_output;
    GraphBlockInput *_input;
    QColor _color,_colorSelected;
    QPolygonF _symbole;
    IOLink _q;
};

#endif // ARROW_H
