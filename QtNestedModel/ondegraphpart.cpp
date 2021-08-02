#include "drgraphitempart.h"
#include <QMimeData>
#include <QPainter>
#include <QStyleOption>
#include "drgraphconnection.h"

#include <QDebug>

GraphBlockPart::GraphBlockPart(QGraphicsObject *parent)
    : QGraphicsObject(parent)
      ,dragOver(false)
      ,_main(parent)
{
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
QGraphicsObject *GraphBlockPart::getMain(){
    return _main;
}


GraphBlockHeader::GraphBlockHeader(
        std::string name,
        std::string type,
        QGraphicsObject *parent)
    : GraphBlockPart(parent)
    ,_name(name)
    ,_type(type)
    ,_label_1(QString::fromStdString(_type).toUpper())
    ,_label_2(QString::fromStdString(_name))
{
}


QRectF GraphBlockHeader::boundingRect() const
{
    return QRectF(0,-headerheight,headerwidth,headerheight);
}

void GraphBlockHeader::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(isSelected()  ? _cl_header.light(250) : _cl_header);

    painter->drawRoundedRect(boundingRect(), 12, 12);
    QFont font("Times", fonthdr);
    painter->setFont(font);
    painter->drawText(fonthdr,-2*lineheight+fonthdr,_label_1);
    painter->drawText(fonthdr,-lineheight+fonthdr,_label_2);

}
int GraphBlock::type()const{
    return ZType::ZDRAG;
}

//GraphBlockBody::GraphBlockBody(
//        const int h,
//        QGraphicsObject *parent)
//    : GraphBlockPart(parent)
//    ,_h(h)
//{
//}

QRectF GraphBlock::boundingRect() const
{
    return QRectF(0,0, headerwidth, _h);
}

//void GraphBlockBody::paint(QPainter *painter,
//           const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);

//    painter->setBrush(isSelected()  ? _cl_body.light(250) : _cl_body);
//    painter->drawRoundedRect(boundingRect(), 12, 12);
//}

GraphBlockIO::GraphBlockIO(
        ParamQueryBO q,
        int offsy,
         const std::pair<std::string, bool> &l,
        QGraphicsObject *parent)
    : GraphBlockPart(parent)
    ,_label(QString::fromStdString(l.first))
    ,_hasconnector(l.second)
    ,_offsy(offsy)
    ,_query(q)
{

}




void GraphBlockInput::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    Q_UNUSED(widget);
//    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
//    if (lod < 0.2) {
//    }else{

        QFont font("Times", fontio);
        font.setStyleStrategy(QFont::ForceOutline);
        painter->setFont(font);
//        painter->save();
        painter->drawText(QRect{2*plugsize,_offsy,headerwidth,lineheight},Qt::AlignLeft,_label);

//        painter->drawText(10+plugsize,_offsy,_label);
        if(_hasconnector){
            painter->setBrush(isSelected()?
                                  _cl_plug.light(250):
                                  _cl_plug);
            painter->drawEllipse(
            {
                            -plugsize,
                            _offsy+2*plugsize
                        },
                        plugsize,
                        plugsize);
//            painter->restore();
        }
//        painter->setBrush(isSelected()? color.light(130) : color);
//        painter->drawRoundedRect(boundingRect(), 5, 5, Qt::RelativeSize);

//    }

}
QRectF GraphBlockInput::boundingRect() const
{
     return _hasconnector?
                 QRectF(-2*plugsize,_offsy+plugsize, plugsize*2, plugsize*2):
                 QRectF();
}
int GraphBlockInput::type()const{
    return ZType::ZINPUT;
}
int GraphBlockHeader::type()const{
    return ZType::ZHEADER;
}

int GraphBlockOutput::type()const{
    return ZType::ZOUTPUT;
}

QRectF GraphBlockOutput::boundingRect() const
{
    return _hasconnector? QRectF(headerwidth,_offsy+plugsize, plugsize*2, plugsize*2) :
                          QRectF();
}

void GraphBlockOutput::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    (void)(option);
    (void)(widget);
    QFont font("Times", fontio);
//    font.setStyleStrategy(QFont::ForceOutline);
    painter->setFont(font);
//    painter->save();
    painter->drawText(
                QRect{
                    -2*plugsize,
                    _offsy,
                    headerwidth,
                    lineheight
                },
                Qt::AlignRight,_label);
    if(_hasconnector){
        painter->setBrush(isSelected()  ? _cl_plug.light(250) : _cl_plug);
        painter->drawEllipse({
                        headerwidth+plugsize,
                                 _offsy+2*plugsize
                    },
                    plugsize,
                    plugsize);
//        painter->restore();
    }
}
void GraphBlockOutput::addArrow(DrGraphConnection *arrow)
{
    _arrows.append(arrow);
}

void GraphBlockOutput::removeArrow(DrGraphConnection *arrow)
{
    int index = _arrows.indexOf(arrow);
    if (index != -1)
        _arrows.removeAt(index);
}

void GraphBlockOutput::removeArrows()
{
    _arrows.clear();
}


void GraphBlockInput::setArrow(DrGraphConnection *arrow)
{
    _arrow = arrow;
}
void GraphBlockInput::removeArrow()
{
    _arrow = nullptr;
}


static int hauteurCorps(const GraphBlockData& data){
    return
            std::max(data._inputs.size(),data._outputs.size())*lineheight+
            2*lineheight;
}

GraphBlock::GraphBlock( GraphBlockData& data)
//    : GraphBlockPart(nullptr)
    :GraphBlockPart(nullptr)
    ,_w(headerwidth)
    ,_h(hauteurCorps(data))
    ,_label(data._name)
    ,_type(data._type)
{

//    setFlag(ItemHasNoContents);
//    auto *corps = new GraphBlockBody(_h,this);
    auto *headItem = new GraphBlockHeader(data._name,data._type,this);
    int ypos = inputoffsy;
    for(auto& b : data._inputs){
        auto obj = new GraphBlockInput({data._name,b.first},ypos,b,this);
        _inputs.push_back(obj);
        ypos+=lineheight;
    }
    ypos = inputoffsy;
    for(auto& b : data._outputs){
        auto obj = new GraphBlockOutput({data._name,b.first},ypos,b,this);
        _outputs.push_back(obj);
        ypos+=lineheight;
    }
    headItem->setPos(0,0);
//    corps->setPos(0,48);

}


void GraphBlock::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
//    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(isSelected()  ? _cl_body.light(250) : _cl_body);
    painter->drawRoundedRect(boundingRect(), 12, 12);


}

GraphBlockInput * GraphBlock::getInputBlock(const std::string& str){
    for(auto o : _inputs){
        if(o->getLabel().toStdString() == str)
            return o;
    }
    qInfo() << QString::fromStdString("NOPE_IN     " + str);
    return nullptr;
}

GraphBlockOutput * GraphBlock::getOutputBlock(const std::string& str){
    for(auto o : _outputs){
        if(o->getLabel().toStdString() == str)
            return o;
    }
    qInfo() << QString::fromStdString("NOPE_OUT     " + str);
    return nullptr;
}
const std::string& GraphBlock::labelObjet(){
    return _label;
}

const std::string& GraphBlock::typeObjet(){
    return _type;

}
Supprimable::Supprimable()
    :_selected(false)
{}

Supprimable::~Supprimable(){

}

GraphBlockPart::~GraphBlockPart(){

}
GraphBlockHeader::~GraphBlockHeader(){

}
//GraphBlockBody::~GraphBlockBody(){

//}
GraphBlockIO::~GraphBlockIO(){

}
GraphBlockInput::~GraphBlockInput(){
//    delete _arrow;
}
GraphBlockOutput::~GraphBlockOutput(){
//    for(auto arr : _arrows){
//        delete arr;
//    }
}
GraphBlock::~GraphBlock(){

}
GraphBlockOp::~GraphBlockOp(){

}
GraphBlockMIDIDevice::~GraphBlockMIDIDevice(){

}

void GraphBlockInput::selection(bool st){
    if(_arrow != nullptr)
        _arrow->_selected = st;
}

void GraphBlockInput::invselection(){
    if(_arrow != nullptr)
        _arrow->_selected = !_arrow->_selected;
}


void GraphBlockOutput::selection(bool st){
    for(auto a : _arrows){
        a->_selected = st;
    }
}

void GraphBlockOutput::invselection(){
    for(auto a : _arrows){
        a->_selected = !a->_selected;
    }
}
