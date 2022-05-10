#ifndef BOIO_H
#define BOIO_H

#include <string>
#include <list>

typedef std::list<std::string> StringList;

struct data2D{
    double x,y;
};


struct ParamQuery{
    std::string module,port;
    bool operator==(const ParamQuery& otr)const{
        return otr.module == module && otr.port == port ;
    }
};

struct IOLink{
    ParamQuery output,input;
};

struct ModuleBO{
    std::string name;
    StringList inputs,outputs;
    bool readonly;
    bool canAddOutputs;
    bool canAddInputs;
};


struct ModuleMAnager{
    std::string name;
    std::list<ModuleBO> modules;
};

struct IOAliases{

    std::string _name     ;
    std::string _nickname  ;
    bool _active   ;
    bool _plugged ;
};

#endif // BOIO_H
