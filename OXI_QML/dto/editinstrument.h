#ifndef EDITINSTRUMENT_H
#define EDITINSTRUMENT_H

#include "editable.h"

struct InstrumentEditor
        :Repository{
    void modifierPolyphonie(
            int poly);
    void modifierNom(
            const std::string& nnom);
    void modifierPrototype(
            const std::string& proto);
    void supprimerSortie(
            const std::string& nomsortie);
    void addOutput(
             const std::string& nomsortie);
};


#endif // EDITINSTRUMENT_H
