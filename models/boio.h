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

//MIDIINPUTS modules with mlidi device name + all channel message (as signal)
//CONSTANTES :  can define name and value, no input. one output
//MATH OPERATION 1 or 2 input , (N inputs  outputs using expressions )
//FILTERS (... from 1 pole to biquad, comb etc
//REVERB (mutliple days  + lowpass, freeverb like
//DYNAMICS (compressor, limiter, tanh
//SAMPLERS (basic reader, to granular synth
//OSCILLATORS (ice, shape , wavetable (DImensions)
//ENVELOPPES (AR, DAR, DADSR , NEnv


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
