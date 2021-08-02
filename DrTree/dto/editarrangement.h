#ifndef EDITARRANGEMENT_H
#define EDITARRANGEMENT_H

#include "editable.h"



struct ArrangementEditor
        :Repository{

    void ajouterCanal(
            const std::string& cigale,
            const std::string& instru
            );
    void supprimerCanal(
            const std::string& cigale,
            const std::string& instru
            );
};



#endif // EDITINSTRUMENT_H
