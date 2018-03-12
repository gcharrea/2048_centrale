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

void pion::decrement()
{
    if (Valeur > 0)
    {
        Valeur--;
        emit pChanged();
    }
}

QString pion::readValeur()
{
    if(Valeur == 0)
        return "";
    return QString::number(pow(2,Valeur));
}
