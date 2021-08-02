#include "drgraphview.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QGraphicsItem>
#include <QDebug>

DrGraphView::~DrGraphView(){
}

DrGraphView::DrGraphView( QGraphicsScene* scene)
    :QGraphicsView(scene)
{
//    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::NoAnchor); //pour permettre la translation
//    setAcceptDrops(true);
//    setInteractive(true);
//    setDragMode(QGraphicsView::RubberBandDrag);
//      setDragMode(QGraphicsView::ScrollHandDrag);
    setDragMode(QGraphicsView::NoDrag);
}
void DrGraphView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void DrGraphView::keyReleaseEvent(QKeyEvent *event) {
    QGraphicsView::keyReleaseEvent(event);
}
void DrGraphView::mouseDoubleClickEvent(QMouseEvent *event) {
    QGraphicsView::mouseDoubleClickEvent(event);
}

void DrGraphView::mousePressEvent(QMouseEvent *event){
    auto it = itemAt(event->pos());
    if(it != nullptr)
        qInfo()<< it->type();
    QGraphicsView::mousePressEvent(event);
}


void DrGraphView::mouseMoveEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
}

void DrGraphView::mouseReleaseEvent(QMouseEvent *event) {
    QGraphicsView::mouseReleaseEvent(event);
}
void DrGraphView::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() >0){
        setZoom(0.1);
    }else{
        setZoom(-0.1);
    }
}


void DrGraphView::deplacerX(double v){
    translate(v,0);
}
void DrGraphView::deplacerY(double v){
    translate(0, v);
}
void DrGraphView::deplacerXY(double dx,double dy){
    translate(dx,dy);
//    setZoom(0.0);
}

const QRectF DrGraphView::bornesVisibles() const{
    auto vprec = QRect(0,0,viewport()->width(),viewport()->height());
    return mapToScene(vprec).boundingRect();
}


static const QPointF getCentre(const QRectF& r ) {
    return QPointF{

        r.x()+r.width()/2,
        r.y()+r.height()/2
    };
}


void DrGraphView::setZoom(double v){

    if(v<=-1.0) return;
    auto c0 =getCentre(bornesVisibles());
    scale( 1.0+v,1.0+v);
    centerOn(c0);
}

