#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include "drgraphlabel.h"
#include "treestyle.h"
#include "drgraphitempart.h"
#include "drgraphcursor.h"


class DrGraphScene
        : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DrGraphScene(
            GraphModel &model,
            QObject *parent = 0);

    double getZoom()const;
    void setZoom(const double);
    TreeStyle& style(){return _style;}
    FontUser& fontUser(){return _fontUser;}
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void moveit(const QPointF& pt );
    void updateCursor();
    QRect cursorRect();
    static GraphBlock * getByName(const std::list<GraphBlock *>& bs,const std::string& b);
private:
    bool isItemChange(int type);
    GraphModel& _model;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    DrGraphLabel *textItem;
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;

    double _zoom;
    FontUser _fontUser;
    TreeStyle _style;
    QPointF _seloffset;

    DrGraphCursor _ghost;
//    bool _isPressed;
    std::list<GraphBlock *> _blocks;
    std::list<DrGraphConnection *> _conns;

};

#endif // DIAGRAMSCENE_H
