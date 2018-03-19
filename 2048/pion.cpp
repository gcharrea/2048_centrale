#include "pion.h"
#include <cmath>

pion::pion(QObject *parent) : QObject(parent)
{
    Valeur = 0;
    emit pChanged();
}

void pion::increment()
{
    Valeur++;
    emit pChanged();
}

QString pion::readValeur()
{
    if(Valeur == 0)
        return "";
    return QString::number(pow(2,Valeur));
}

int pion::valeurPion()
{
    return Valeur;
}

void pion::free()
{
    Valeur = 0;
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
    return *this;
}

pion& pion::operator =(int v){
    Valeur = v;
    return *this;
}
