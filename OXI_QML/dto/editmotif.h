#ifndef EDITMOTIF_H
#define EDITMOTIF_H

#include "editable.h"


//un motif classic est un selector  avec seulement une valeur par defaut
struct MotifEditor
        :Repository{
    void nommer(const std::string& name);
    void ajouterMotif(const std::string& m);
    void supprimer(const std::string& m);
    void remplacer(const std::string& m,const std::string& nm);
};

struct MotifPickSelector
        :Repository{
    void nommer(const std::string& name);
    void setMotifPick(int num,const std::string& m);
    void setDefaultMotifPick(int num,const std::string& m);
};

struct MotifPickable
        :Repository{
    void nommer(const std::string& name);
    void setMotif(const std::string& name);
    void setPressedNotes(int num);
    void setTimeSignature(int mult, int div);
    void setResync(bool);
};

struct SequenceNoteEditor
        :Repository{
    void nommer(const std::string& name);
    void rogner(double from, double to);
    void modifierDuree(int en, double t);
    void modifierNote(int en, int nn);
    void modifierVelocite(int en, int nn);
};

struct SequenceControlEditor
        :Repository{
    void nommer(const std::string& name);
    void rogner(double from, double to);
    void modifierNum(int en, int nn);
    void modifierValeur(int en, int nn);
};

#endif // EDITINSTRUMENT_H
