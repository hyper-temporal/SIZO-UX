#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <QGraphicsItem>

//elements producteurs:
//les objets qui permettent d'instancier un objet
//pour recupérer l'interface je peux instancier un objet temporairement
//et recup ses io ainsi:
//auto is = obj.
// ressources de bases: (NomEtType) _signaux
/**
str_rsc_icek
str_rsc_ice
str_rsc_env
str_rsc_aleatoire
str_rsc_mixeur
str_rsc_repartiteur
*/
//ressources complexes
/**
EnveloppeAnyBO  _envanyz
Granular_BO     _granulars
HyperWave_BO    _hypewaves
ImpactSynth_BO  _impactSynths
CompoundBO      _shps
CompoundBO      _shpsK
FX_FilterCtrl_BO       _filtres
*/
//operations entre signaux
/**
CompoundBO _formulas
*/
//connections simples O=>I
/**
Connexion_BO  _connections
Constante_BO _initialisation
*/

// FX
/**
str_fx_Rev
str_fx_Limit
str_fx_Filtre
str_fx_Distortion
str_fx_Generic
 */


class Element
        : public QGraphicsItem
{

public:
    enum { Type = UserType + 1 };
    Element(
//            std::string& name,
//            std::list<std::string>& inputs,
//            std::list<std::string>& outputs
            );

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override{ return Type; }
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QColor color;
};



class ElementStore
{
public:
    static std::list<Element> creerElements();


};

#endif
