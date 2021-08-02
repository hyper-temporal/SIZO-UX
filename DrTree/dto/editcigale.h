#ifndef EDITCIGALE_H
#define EDITCIGALE_H

#include "editable.h"



struct CigaleEditor
        :Repository{

    void setNom(const std::string& name);
    void ajouterChannelFiltre(int ch);
    void supprimerChannelFiltre(int ch);
    void ajouterNoteOK(int mi,int ma);
    void supprimerNoteOK(int mi,int ma);
    void ajouterVelocOK(int mi,int ma);
    void supprimerVelocOK(int mi,int ma);
    void setCible(int dev,int ch);
    void ajouterMethode0D(const std::string& m,short de, short ty,short ch, short dt1, short dt2);
    void ajouterMethode1D(const std::string& m,short de, short ty,short ch, short dt1);
    void ajouterMethode2D(const std::string& m,short de, short ty,short ch);
    void supprimerMethode0D(const std::string& m);
    void supprimerMethode1D(const std::string& m);
    void supprimerMethode2D(const std::string& m);
    void ajouterProjection(short ni, short no);
    void supprimerProjection(short ni, short no);
    void ajouterMotif(const std::string& m);
    void supprimerMotif(const std::string& m);
};


#endif // EDITINSTRUMENT_H
