#include "pion.h"
#include <cmath>

pion::pion(QObject *parent) : QObject(parent)
{
    Valeur = 0;
    changeCouleur();
}

void pion::increment()
{
    Valeur++;
    changeCouleur();
}

QList<QString> pion::readPion()
{
    QList<QString> parametres;
    if(Valeur == 0)
        parametres.append("");
    else
        parametres.append(QString::number(pow(2,Valeur)));
    parametres.append(Couleur);
    return parametres;
}

int pion::valeurPion()
{
    return Valeur;
}

void pion::free()
{
    Valeur = 0;
    changeCouleur();
}

bool pion::isVide()
{
    return Valeur == 0;
}

bool pion::operator ==(const pion &p)
{
    return Valeur == p.Valeur;
}

pion& pion::operator =(const pion &p)
{
    Valeur = p.Valeur;
    Couleur = p.Couleur;
    return *this;
}

pion& pion::operator =(int v){
    Valeur = v;
    changeCouleur();
    return *this;
}

void pion::changeCouleur(){
    QString couleurs []=   {"lightgrey","ghostwhite","beige","lightsalmon","coral",
                            "tomato","orangered","#ffe44d","#ffe033","#ffdd1a",
                            "#f9d406","gold","#42a51c","orchid"};
    Couleur = couleurs[Valeur%14];
}
