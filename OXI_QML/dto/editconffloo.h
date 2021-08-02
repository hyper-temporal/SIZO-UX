#ifndef EDITCONFFLOO_H
#define EDITCONFFLOO_H

#include "editable.h"


struct FlooConfEditor
        :Repository{

    void ajouterEntreeMIDI(const std::string& m);
    void ajouterSortieMIDI(const std::string& m);
    void supprimerEntreeMIDI(const std::string& m);
    void supprimerSortieMIDI(const std::string& m);
    void ajouterMethode0D(const std::string& m,short de, short ty,short ch, short dt1, short dt2);
    void ajouterMethode1D(const std::string& m,short de, short ty,short ch, short dt1);
    void ajouterMethode2D(const std::string& m,short de, short ty,short ch);
    void supprimerMethode0D(const std::string& m);
    void supprimerMethode1D(const std::string& m);
    void supprimerMethode2D(const std::string& m);
    void ajouterCigale(const std::string& m);
    void supprimerCigale(const std::string& m);
};

#endif // EDITINSTRUMENT_H
