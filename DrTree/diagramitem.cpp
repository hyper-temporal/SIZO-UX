#include "drgraphitem.h"
#include "drgraphconnection.h"


static void fillPolygone(DiagramItem::DiagramType typ, QPolygonF& po )
{
    QPainterPath path;
    switch (typ) {
        case DiagramItem::StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            po = path.toFillPolygon();
            break;
        case DiagramItem::Conditional:
            po << QPointF(-100, 0) << QPointF(0, 100)
               << QPointF(100, 0) << QPointF(0, -100)
               << QPointF(-100, 0);
            break;
        case DiagramItem::Step:
            po << QPointF(-100, -100) << QPointF(100, -100)
               << QPointF(100, 100) << QPointF(-100, 100)
               << QPointF(-100, -100);
            break;
        default:
            po << QPointF(-120, -80) << QPointF(-70, 80)
               << QPointF(120, 80) << QPointF(70, -80)
               << QPointF(-120, -80);
            break;
    }
}

DiagramItem::DiagramItem(
        DiagramType diagramType,
        QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent)
{
    myDiagramType = diagramType;
    fillPolygone(diagramType,myPolygon);
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramItem::removeArrow(DrGraphConnection *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
    foreach (DrGraphConnection *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(DrGraphConnection *arrow)
{
    arrows.append(arrow);
}

QPixmap DiagramItem::image() const
{
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));
    painter.translate(125, 125);
    painter.drawPolyline(myPolygon);

    return pixmap;
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
//    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (DrGraphConnection *arrow, arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}
