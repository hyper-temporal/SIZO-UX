#include "drgraphe.h"
#include <QPainter>
#include <QLineF>
#include <QSGSimpleRectNode>
#include <QDebug>
#include <QWheelEvent>
#include <QGraphicsWidget>

#include "drgraphitempart.h"
#include "drgraphconnection.h"
#include "objectstore.h"
#include "jeudetest.h"


DrGraphe::DrGraphe(QQuickItem *p)
    :QQuickPaintedItem(p),
      _vue(nullptr),
      _scene(nullptr),
      _cursorSize(10.0) ,
      _moving(false),
      _line(nullptr),
      _output(nullptr),
      _connecting(false),
      _ghostcursor()
{

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);
    setCursor(Qt::BlankCursor);

    GraphModel model ={
        "I'm scared",
        BlockDataList{
            GraphBlockData{
                "my names is", //std::string _name;
                "my type is", //std::string _type;
                {{"input 1", true},{"input 2", false},{"input 3", true}},//std::list<std::pair<std::string,bool>> _inputs;
                {{"output 1", true},{"output 2", false},{"output 3", true}},//std::list<std::pair<std::string,bool>> _inputs;
            },
            GraphBlockData{
                "my other name is", //std::string _name;
                "my other type is", //std::string _type;
                {{"input 1", true},{"input 2", false},{"input 3", true}},//std::list<std::pair<std::string,bool>> _inputs;
                {{"output 1", true},{"output 2", false},{"output 3", true}},//std::list<std::pair<std::string,bool>> _inputs;
            }
        },
        ConnectionList{}
    };

    setModel(model);


}


void DrGraphe::setModel(const GraphModel& model){
    _model = model;
    if(_vue != nullptr)
        delete _vue;
    if(_scene != nullptr)
        delete _scene;
    _scene = new DrGraphScene(_model,this);
    _vue = new DrGraphView(_scene);

    zoom(0.01);
}

DrGraphe::~DrGraphe(){
}

template<typename T>
double hypothenuse(T cx, T cy , T mx, T  my){
    auto distx = (mx-cx);
    auto disty = (my-cy);
    return sqrt(distx*distx + disty*disty);
}

bool DrGraphe::getHoveredAccepted(){
    return _hoveredAccepted;
}
void DrGraphe::setHoveredAccepted(bool v){
    _hoveredAccepted = v;
    setAcceptHoverEvents(_hoveredAccepted);
}


void DrGraphe::addCentreX(double v){
    _vue->deplacerX(v);
}
void DrGraphe::addCentreY(double v){
    _vue->deplacerY(v);
}

void DrGraphe::zoom(double v){
    _vue->setZoom(v);
}

void DrGraphe::deleteSelection(){
    for(auto s : _selected){
        delete s;
    }
}




void DrGraphe::setFontSize(int v){
    if(v >=1 ){
        _scene->fontUser().setFontSize(v);
    }
}

int DrGraphe::getFontSize()const{
    return _scene->fontUser()._fontSize;
}
QGraphicsItem * DrGraphe::getPlugOrDrag(QPoint& pos){
    auto li = _vue->items(pos);
    for(auto gi : li){
        if(gi->type() == ZType::ZINPUT ){
            return gi;
        }
    }
    for(auto gi : li){
        if( gi->type() == ZType::ZOUTPUT){
            return gi;
        }
    }
    for(auto gi : li){
        if(gi->type() == ZType::ZDRAG || gi->type() == ZType::ZHEADER){
            return gi;
        }
    }
    for(auto gi : li){
        if(gi->type() == ZType::ZCONNECT ){
            return gi;
        }
    }
    return nullptr;
}


void DrGraphe::mousePressEvent(QMouseEvent *me)
{
    if(_moving)return;
    auto po = me->pos();
    auto posc = _vue->mapToScene(po);
    if(me->button() == Qt::RightButton){
        _pastPoint = po;
        _moving = true;
    }else{
        auto p = getPlugOrDrag(po);
        if(p != nullptr){
            auto anon =  qgraphicsitem_cast<QGraphicsWidget *>(p);

            if( anon != nullptr){
                Logger::log().info("Wi");
            }
            else if(     p->type() == ZType::ZDRAG){
                auto block =  qgraphicsitem_cast<GraphBlock *>(p);
                if(block != nullptr){
                    block->setSelected(true);
                }
            }else if( p->type() == ZType::ZHEADER){
                auto block =  qgraphicsitem_cast<GraphBlockHeader *>(p);
                auto pa = block->getMain();
                if(pa != nullptr){
                    pa->setSelected(true);
                }
            }else if( p->type() == ZType::ZINPUT){
                auto zob =  qgraphicsitem_cast<GraphBlockInput *>(p);
            }else if( p->type() == ZType::ZCONNECT){
                auto zob =  qgraphicsitem_cast<DrGraphConnection *>(p);
//                zob->setSelected(true);
            }else if( p->type() == ZType::ZOUTPUT){
                auto sortie =  qgraphicsitem_cast<GraphBlockOutput *>(p);
                sortie->invselection();
                _output = sortie;
                _line = new QGraphicsLineItem(QLineF(posc, posc));
                _line->setPen(QPen(_clr_Black, 1));
                _scene->addItem(_line);
                _connecting =true;
            }else{
            }
        }
    }
    _vue->mousePressEvent(me);
    me->accept();
    update();
}

void DrGraphe::geometryChanged(const QRectF &ng, const QRectF &og){
    _vue->setGeometry(ng.toRect());
    update();
}

//a comprendre: le point semble deja mappé (approximativement) par le qgraphic(painted)item
void DrGraphe::mouseMoveEvent(QMouseEvent *me){
    auto po = me->pos();
    if(_moving){
        double dx =  po.x()- _pastPoint.x() ;
        double dy = po.y()- _pastPoint.y() ;
        _vue->deplacerXY(dx,dy);
    }else if (_connecting == true && _line != nullptr) {
        auto posc = _vue->mapToScene(po);
        QLineF newLine(_line->line().p1(), posc);
        _line->setLine(newLine);
    }
    _vue->mouseMoveEvent(me);
    _pastPoint = po;
    me->accept();
    update();
}

void DrGraphe::hoverMoveEvent(QHoverEvent *me){
    auto pos = me->pos();
    auto et =  QEvent::MouseMove;
    auto mb =  Qt::MouseButton::ExtraButton23;
    auto mbs = Qt::MouseButton::ExtraButton23;
    auto km = Qt::NoModifier;
    QMouseEvent eme (et,pos,mb,mbs,km);
    _vue->mouseMoveEvent(&eme);
    //    QGraphicsItem* p = getPlugOrDrag(pos);
    //    unsetCursor();

    //    if(p!= nullptr){
    //        if( p->type() == ZType::ZDRAG ||  p->type() == ZType::ZHEADER){
    //            setCursor(Qt::OpenHandCursor);
    //        }else if( p->type() == ZType::ZINPUT){
    //            setCursor(Qt::PointingHandCursor);
    //        }else if( p->type() == ZType::ZCONNECT){
    //            setCursor(Qt::PointingHandCursor);
    //        }else if( p->type() == ZType::ZOUTPUT){
    //            setCursor(Qt::ArrowCursor);
    //        }
    //        else{
    //            setCursor(Qt::CrossCursor);
    //        }

    //    }else{
    //        setCursor(Qt::CrossCursor);
    //    }
    _scene->updateCursor();
    //    auto screc = _scene->cursorRect();
    //    auto mscrec = QRect{
    //            _vue->mapFromScene(screc.topLeft()),
    //            _vue->mapFromScene(screc.bottomRight())
    //    };
    //    update(mscrec);
    update();
    me->accept();
}

void DrGraphe::keyPressEvent(QKeyEvent *event){
    qInfo() << "press" <<event->key();
}

void DrGraphe::keyReleaseEvent(QKeyEvent *event){
    qInfo() << "release" <<event->key();
}

void DrGraphe::wheelEvent(QWheelEvent *me){
    _vue->wheelEvent(me);
    me->accept();
    update();
}

void DrGraphe::mouseReleaseEvent(QMouseEvent *me){
    auto pos = me->pos();
    if(me->button() == Qt::RightButton){
        _moving =false;
    }
    else if(me->button() == Qt::LeftButton){
        //        _scene->setPressed(false);
        if( _line != nullptr &&
                _connecting == true )
        {
            //elevere la ligne sinon c'est elle qui est trouvee
            _scene->removeItem(_line);
            delete _line;
            _line = nullptr;
            QGraphicsItem* obj = getPlugOrDrag(pos);
            if(obj!= nullptr){
                //            qInfo()<<obj->type();
                if( obj->type() == ZType::ZINPUT){
                    auto entree =  qgraphicsitem_cast<GraphBlockInput *>(obj);
                    if(
                            entree != nullptr     &&
                            _output != nullptr
                            ){
                        DrGraphConnection *arrow = new DrGraphConnection(_output, entree);
                        arrow->setColor(_clr_Blue);
                        _output->addArrow(arrow);
                        entree->setArrow(arrow);
                        arrow->setZValue(-1000.0);
                        arrow->setVisible(true);
                        arrow->setVisible(true);
                        _scene->addItem(arrow);
                        //                    _vue->update();
                    }
                }
            }
            _connecting = false;
        }
    }
    _pastPoint = pos;
    _vue->mouseReleaseEvent(me);
    me->accept();
    update();

}

void DrGraphe::paint(QPainter *pntr){
    pntr->setRenderHint(QPainter::Antialiasing, true);
    _vue->render(pntr);
}

