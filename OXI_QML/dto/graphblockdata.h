#ifndef GRAPHBLOCKDATA_H
#define GRAPHBLOCKDATA_H

#include <string>
#include <list>
#include <boio.h>


typedef  std::list<Connexion_BO>  ConnectionList;
typedef  std::pair<std::string&,double&> ParameterInterne;

//pour construire un prototype: une liste de GraphBlockData + un name
//les references permettrons la modification
struct GraphBlockData{
    std::string _name;
    std::string _type;
    std::list<std::pair<std::string,bool>> _inputs;
    std::list<std::pair<std::string,bool>> _outputs;
    int _x, _y;
//    bool _canAddInput;
//    bool _canAddOutput;
//    std::list<ParameterInterne> _parametersInternes;
    static void merge(GraphBlockData& me, GraphBlockData& oth ){
        me._inputs.insert(me._inputs.end(),oth._inputs.begin(),me._outputs.end());
        me._outputs.insert(me._outputs.end(),oth._outputs.begin(),me._outputs.end());
    }
    static GraphBlockData defaultConstruct(){
        return{
            "",
            "",
            {},
            {},
            0,
            0
        };
    }
};

typedef std::list<GraphBlockData> BlockDataList;


struct GraphModel{
    std::string _name;
    BlockDataList modules;
    ConnectionList _connections;
};



#endif // GRAPHBLOCKDATA_H
