#include "drgraphscene.h"
#include "drgraphconnection.h"
#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <logger.h>



static void instancierLesBlocs(
        GraphModel& model,
        std::list<GraphBlock*>& lst)
{
    for(GraphBlockData& o : model.modules){
        auto item = new GraphBlock(o);
        item->setPos(o._x,o._y);
        lst.push_back(item);
    }
}

static bool ioExiste(
        const std::string& name,
        std::list<std::pair<std::string,bool>>& ios)
{

    for(auto& io : ios){
        if(io.first == name)
            return true;
    }
    return false;
}



static GraphBlock * getModule(
        std::list<GraphBlock *>& blocs,
        const std::string& nm)
{
    for(GraphBlock* c : blocs){
        if(nm == c->labelObjet()){
            return c;
        }
    }
    return nullptr;
}
//comme l'autre mais on doit parser le name
static GraphBlockOutput * getOperationLinkedBlock(
        std::list<GraphBlock *>& blocs,
        const std::string& nm)
{
    auto mo = getModule(blocs,nm);
    if(mo != nullptr)
        return mo->getOutputBlock(nm);
    else
        Logger::log().error("module non trouvé:"+ nm);

}



static bool connectionExists(
        const IOLink* conn,
        std::list<DrGraphConnection *>conns)
{

    for(const DrGraphConnection* c : conns){
        const auto q = c->getQuery();
        if(   conn ==  q  ){
            return true;
        }
    }
    return false;
}

static DrGraphConnection* creerConnection(
        IOLink q,
        GraphBlockOutput * bout ,
        GraphBlockInput * bin  )
{

    if(bin != nullptr && bout != nullptr){
        auto connection = new DrGraphConnection(bout,bin);
        bout->addArrow(connection);
        bin->setArrow(connection);
        connection->setZValue(-1000.0);
        connection->setVisible(true);
        return connection;
    }
    return nullptr;
}
static std::pair<GraphBlockOutput *,GraphBlockInput * > tryConnect(
        const IOLink c,
        std::list<GraphBlock *>& blocs
        )
{
    GraphBlockOutput * bout = nullptr;
    GraphBlockInput * bin = nullptr;
    auto modO = getModule(blocs,c.output.module);
    auto modI = getModule(blocs,c.input.module);
    if(modO != nullptr)
        bin = modO->getInputBlock(c.input.port);
    if(modI != nullptr)
        bout = modI->getOutputBlock(c.input.port);
    return {bout,bin};
}



DrGraphScene::DrGraphScene(
        GraphModel& m,
        QObject *parent)
    : QGraphicsScene(parent)
    ,_model(m)
    ,_ghost()
{
    std::list<ParamQuery> outputnotfound;
    std::list<ParamQuery> inputnotfound;
    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    addItem(&_ghost);//histoire de pas donner un placement debile au curseur car sinon il se retrouve a perpet
    _ghost.setPos(_model.modules.front()._x,_model.modules.front()._y);
    instancierLesBlocs(_model,_blocks);
    for(auto it : _blocks){
        addItem(it);
    }
    //connections simples
    for( IOLink& co : _model._connections){
        auto it = tryConnect(co, _blocks);
        auto bout = it.first;
        auto bin = it.second;
        DrGraphConnection * con = creerConnection(co,bout,bin);
        if(con == nullptr){
            if(bout == nullptr){
                outputnotfound.push_back(co.output);}
            if(bin == nullptr){
                inputnotfound.push_back(co.input);}
        }else{
            addItem(con);
            _conns.push_back(con);
        }
    }
    //PRE...
    ///un signal d'entree d'operation ou de connection
    ///refere a un signal de sortie existant localement ou PRE


    //je reexecute la procedure de connection car les op
    for( const IOLink& co : _model._connections)
    {
        if(!connectionExists(&co,_conns)){
            auto it = tryConnect(co , _blocks);
            auto bout = it.first;
            auto bin = it.second;
            DrGraphConnection * con = creerConnection(co,bout,bin);
            if(con == nullptr){
                if(bout == nullptr){
                    outputnotfound.push_back(co.output);
                }
                if(bin == nullptr){
                    inputnotfound.push_back(co.input);
                }
            }else{
                outputnotfound.remove(co.output);
                inputnotfound.remove(co.input);
                addItem(con);
                _conns.push_back(con);
            }
        }
    }
    for(auto& str : outputnotfound){
        Logger::log().error("le signal *** "
                       + (str.module)+ (str.port)
                       + " *** doit etre créé ou délégué a un graph PRE!"
                       );
    }
    for(auto& str : inputnotfound){
        Logger::log().error("entree inexistante *** "
                      + (str.module)+ (str.port)
                       + " *** "
                       );
    }

}

void DrGraphScene::moveit(const QPointF& pt ){
    if (!selectedItems().empty()){
        for(auto& item : selectedItems()){
            item->moveBy(
                        pt.x(),
                        pt.y()
                        );
        }
    }
}


void DrGraphScene::updateCursor(){
    update(_ghost.boundingRect());
}
QRect DrGraphScene::cursorRect(){
    return  _ghost.boundingRect().normalized().toRect();
}




void DrGraphScene::mousePressEvent(QGraphicsSceneMouseEvent *me)
{
    if(me->button() == Qt::LeftButton){
        _ghost.setPressed(true);
    }
    me->accept();
}

void DrGraphScene::mouseMoveEvent(QGraphicsSceneMouseEvent *me)
{
    auto pos = me->scenePos();
    _ghost.setPos(pos);

    auto lpos = me->lastScenePos();
    _seloffset = {
        pos.x()-lpos.x(),
        pos.y()-lpos.y()
    };

    //    qInfo()<<_seloffset;
    if (!selectedItems().empty()){
        for(auto& item : selectedItems()){
            item->moveBy(_seloffset.x(),_seloffset.y());
        }
    }

    me->accept();
}


static double zoomin = 0.1;
static double zoomax = 4.0;
static double fsmin = 4;
static double fsmax = 48;


void DrGraphScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *me)
{
    if(me->button() == Qt::LeftButton){
        _ghost.setPressed(false);
    }
    for(auto& item : selectedItems()){
        item->setSelected(false);
    }
    me->accept();
}

bool DrGraphScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
GraphBlock * DrGraphScene::getByName(
        const std::list<GraphBlock *>& l,
        const std::string& str)
{
    for(GraphBlock * b : l){
        if(b->labelObjet() == str){
            return b;
        }
    }
    return nullptr;
}
