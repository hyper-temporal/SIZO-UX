#ifndef ONDEGRAPHPART_H
#define ONDEGRAPHPART_H

#include <QLayout>
#include <QLayoutItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QTextOption>
#include "dto/graphblockdata.h"
#include <boio.h>

class DrGraphConnection;
class GraphBlock;

enum ZType
{
    ZDRAG = QGraphicsObject::UserType + 13 ,
    ZHEADER = ZDRAG+1 ,
    ZINPUT = ZHEADER+1 ,
    ZOUTPUT = ZINPUT+1 ,
    ZCONNECT = ZOUTPUT+1
};


class GraphBlockPart
        :public QGraphicsObject
{
public:
    virtual ~GraphBlockPart();
    GraphBlockPart(QGraphicsObject *parent = 0);
    QGraphicsObject *getMain();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override{(void)event;}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override{(void)event;}
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override{(void)event;}
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override{(void)event;}
    void wheelEvent(QGraphicsSceneWheelEvent *event)override{(void)event;}
    bool dragOver;
    QGraphicsObject *_main;
};


class GraphBlockHeader
        : public GraphBlockPart
{
public:
    virtual ~GraphBlockHeader();
    GraphBlockHeader(
            const std::string str,
            const std::string type,
            QGraphicsObject *parent);
    QRectF boundingRect() const override;
    int type() const override;
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget = 0) override;
//    void changerNom(const std::string& name);
//    void setValeurParDefaut(const std::string& name);
protected:
private:
    QPixmap pixmap;
    std::string _name;
    const std::string _type;
    const QString _label_1,_label_2;
};



class GraphBlockIO
        :public GraphBlockPart
{
public:
    virtual ~GraphBlockIO();
    GraphBlockIO(
            ParamQuery q,
            int offsy,
            const std::pair<std::string,bool>  &l,
            QGraphicsObject *parent);
    const QString& getLabel(){return _label;}
    virtual void selection(bool)=0;
    virtual void invselection()=0;
    const ParamQuery& query(){return _query;}
protected:
    QString _label;
    bool _hasconnector;
    int _offsy;
private:
    ParamQuery _query;
};


class GraphBlockInput
        : public GraphBlockIO
{
    bool _selected;

public:
    virtual ~GraphBlockInput();
    GraphBlockInput(
            ParamQuery q,
            int ofy,
            std::pair<const std::string&,bool> l,
            QGraphicsObject *p)
        :GraphBlockIO(q,ofy,l,p)
        ,_selected(false)
    {}
    int type() const final;
    QRectF boundingRect() const final;
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget) final;
    void removeArrow();
    void setArrow(DrGraphConnection *arrow);
    void updatePosition();
    void selection(bool);
    void invselection();
private:
    QStringList _connections;
    DrGraphConnection * _arrow;
};

class GraphBlockOutput
        : public GraphBlockIO
{
public:
    virtual ~GraphBlockOutput();
    GraphBlockOutput(
            ParamQuery q,
            int ofy,
             const std::pair<std::string, bool> &l,
            QGraphicsObject *p)
        :GraphBlockIO(q,ofy,l,p)
    {}
    int type() const final;
    QRectF boundingRect() const final;
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget) final;

    void selection(bool);
    void invselection();
    void removeArrow(DrGraphConnection *arrow);
    void removeArrows();
    void addArrow(DrGraphConnection *arrow);
//    void updatePosition();
private:
    QList<DrGraphConnection *> _arrows;

};

class GraphBlock
        :public GraphBlockPart
{
public:
    virtual ~GraphBlock();
    GraphBlock(GraphBlockData& data);
    QRectF boundingRect() const override;
    void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget = 0) override;

    int type() const override;
    GraphBlockInput* getInputBlock(const std::string &str);
    GraphBlockOutput* getOutputBlock(const std::string& str);

    const std::string& labelObjet();
    const std::string& typeObjet();
protected:
private:
    const int _w,_h;
    QList<GraphBlockOutput*> _outputs;
    QList<GraphBlockInput*> _inputs;
    std::string _label;
    std::string _type;

};

class GraphBlockOp
        : public GraphBlock
{
public:
    virtual ~GraphBlockOp();
    GraphBlockOp(GraphBlockData& data)
        :GraphBlock(data){}
    //void onCreate(const std::string& em,const std::string& rec );
    //void onDelete(const std::string& em,const std::string& rec );
};

class GraphBlockMIDIDevice
        : public GraphBlock
{
public:
    virtual ~GraphBlockMIDIDevice();
    GraphBlockMIDIDevice(GraphBlockData& data)
        :GraphBlock(data){}
//    void changerNom(const std::string& name);
//    void addOutput(const std::string& dev, int typ, int ch, int num );
};

static int headerwidth     = 256                ;
static int lineheight      = 24                 ;
static int headerheight    = 3*lineheight                 ;
static int inputoffsy     = lineheight ;
static int plugsize = 10;
static int fonthdr = 20;
static int fontio = 10;

static QColor _transparent = QColor(255,0,0,255);
static QColor _cl_header = QColor(255,255,60,40);
static QColor _cl_body = QColor(50,80,120,40);
static QColor _cl_plug = QColor(255,255,0,40);
static QColor _cl_input = QColor(200,170,150,50);
static QColor _cl_output =  QColor(200,170,150,50);




#endif // OndeGraphPart_H
