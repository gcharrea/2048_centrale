#include "pion.h"
#include <cmath>

pion::pion(QObject *parent) : QObject(parent)
{
    Valeur = 1;
    emit pChanged();
}

void pion::increment()
{
    Valeur++;
    emit pChanged();
}

void pion::decrement()
{
    if (Valeur > 1)
    {
        Valeur--;
        emit pChanged();
    }
}

QString pion::readValeur()
{
    return QString::number(pow(2,Valeur));
}
