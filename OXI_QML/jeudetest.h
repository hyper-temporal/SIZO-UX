#ifndef JEUDETEST_H
#define JEUDETEST_H

#include <vector>
#include "dto/graphblockdata.h"

struct JeuDeTest
{

    static std::vector<int> lignes(){
        return {
            0,1,2,3,4,12,64
        };
    }

    static std::string mockNom1(){
        return  "block01";
    }
    static std::string mockNom2(){
        return "block02";
    }


};
#endif // JEUDETEST_H
