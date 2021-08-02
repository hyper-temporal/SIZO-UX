#ifndef BOIO_H
#define BOIO_H

#include <string>
#include <list>

typedef std::list<std::string> StringList;

struct data2D{
    double x,y;
};


struct ParamQueryBO{
    std::string module,io;
    bool operator==(const ParamQueryBO& otr)const{
        return otr.module == module && otr.io == io ;
    }
};

struct Connexion_BO{
    ParamQueryBO output,input;
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
    std::string _nick  ;
    bool _actif   ;
    bool _plugged ;
};

#endif // BOIO_H
