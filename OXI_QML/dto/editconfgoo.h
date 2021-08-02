#ifndef EDITCONFGOO_H
#define EDITCONFGOO_H

#include "editable.h"


struct GooConfEditor
        :Repository{

    void setNom(const std::string& m);
    void setRefreshRate(int rr);
    void ajouterEntreeMIDI(const std::string& m);
    void ajouterSortieMIDI(const std::string& m);
    void supprimerEntreeMIDI(const std::string& m);
    void supprimerSortieMIDI(const std::string& m);

    void setEntreeAudio(const std::string& m);
    void setSortieAudio(const std::string& m);
    void setDuplex(const std::string& m);
    void setNbEntreesAudio(int m);
    void setNbSortiesAudio(int m);
    void setEchantillonnage(int m);
    void setBufferSize(int m);
    void setBufferCount(int m);


    void addInstrumentPre(const std::string& m);
    void addInstrumentPost(const std::string& m);

    void removeInstrumentPre(const std::string& m);
    void removeInstrumentPost(const std::string& m);
    void setFX(const std::string& m);

};

#endif // EDITINSTRUMENT_H
