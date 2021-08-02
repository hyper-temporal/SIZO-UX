#ifndef GANTTDATA_H
#define GANTTDATA_H

#include <array>
#include <list>

struct NodeInput
{
    double _start;
    double _end;
    int _id;
    bool operator ==(const NodeInput& v){return this == &v;}

};


struct GantDataIndexe
{
    int _inx;
    NodeInput &_data;
    bool operator ==(const GantDataIndexe& v){return this == &v;}
};

enum DataGrab{

    GRAB_NON=0,
    GRAB_MV=1,
    GRAB_MH=2,
    GRAB_L=3,
    GRAB_R=4,
};

#endif // GANTTDATA_H
