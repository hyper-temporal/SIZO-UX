#ifndef EDITABLE_H
#define EDITABLE_H

#include <string>
#include <list>
#include "genericdto.h"

struct Repository
{

    std::list<UIEventDTO> _events;
    void effacer( const std::string& name, long long timestamp){
        _events.push_back({
                              timestamp,
                              "delete",
                              name
                          });
    }

    void editer( const std::string& contenu, long long timestamp){
        _events.push_back({
                              timestamp,
                              "edit",
                              contenu
                          });
    }
};





#endif // EDITABLE_H
