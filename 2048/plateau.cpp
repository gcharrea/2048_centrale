#include "plateau.h"
#include "pion.h"
#include "random.h"
#include <iostream>

Random alea;

plateau::plateau(QObject *parent, int l, int c) : QObject(parent)
{
    Alloc(l,c);
    emit plateauQMLChanged();
}

void plateau::Alloc(int l, int c)
{
    L = l;
    C = c;
    T = new pion*[L];
    for (int i=0; i<L; i++)
        T[i] = new pion[C];
}

QList<QString>  plateau::readplateauQML()
{
    QList<QString> Pions;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            Pions.append(T[i][j].readValeur());
    return Pions;
}

int plateau::lignes()
{
    return L;
}

int plateau::colonnes()
{
    return C;
}

int plateau::taille()
{
    return L*C;
}

int plateau::casesVides()
{
    int c = 0;

    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
            if (T[i][j].isVide())
                c++;
    return c;
}

void plateau::newTile()
{
    int c = casesVides();
    cout << c << endl;
    if (c==0)
        throw("Perdu !");

    int r = alea.getInt(c) + 1;

    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
            if (T[i][j].isVide())
            {
                r--;
                if (r==0)
                {
                    T[i][j].increment();
                    emit plateauQMLChanged();
                    break;
                }
            }
}

void plateau::newGame()
{
    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
            T[i][j].free();
    newTile();
}


void plateau::gauche()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien, on ne crée pas de nouvelle tuile

    // On supprime les espaces à gauche
    for (int i=0; i<L; i++)
    {
        for (int j=1; j<C; j++)
        {
            int jtemp = j;
            while (jtemp > 0 && T[i][jtemp-1].isVide() && !(T[i][jtemp].isVide()))
            {
                T[i][jtemp-1] = T[i][jtemp];
                T[i][jtemp].free();
                jtemp--;
                changement = true;
            }
        }

    // On effectue ensuite toutes les additions, on pourra rajouter le calcul du score du coup par ici
        for (int j = 0; j<C-1; j++)
        {
            if (T[i][j] == T[i][j+1] && !(T[i][j].isVide()))
            {
                T[i][j].increment();
                T[i][j+1].free();
                changement = true;
            }
        }

    // On va maintenant chercher à supprimer les espaces créés lors des additions
        for (int j=1; j<C; j++)
        {
            int jtemp = j;
            while (jtemp > 0 && T[i][jtemp-1].isVide() && !(T[i][jtemp].isVide()))
            {
                T[i][jtemp-1] = T[i][jtemp];
                T[i][jtemp].free();
                jtemp--;
                changement = true;
            }
        }
    }

    // On rajoute une tuile
    if (changement)
        newTile();
}


void plateau::droite()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien, on ne crée pas de nouvelle tuile

    for (int i=0; i<L; i++)
    {
        //Mouvement
        for (int j=1; j<C; j++)
        {
            int jtemp = j;
            while (jtemp > 0 && T[i][C - jtemp].isVide() && !(T[i][C - 1 - jtemp].isVide()))
            {
                T[i][C - jtemp] = T[i][C - 1 - jtemp];
                T[i][C - 1 - jtemp].free();
                jtemp--;
                changement = true;
            }
        }

        //Addition
        for (int j = 0; j<C-1; j++)
        {
            if (T[i][C-1-j] == T[i][C-2-j] && !(T[i][C-1-j].isVide()))
            {
                T[i][C-2-j].increment();
                T[i][C-1-j].free();
                changement = true;
            }
        }

        //Mouvement
        for (int j=1; j<C; j++)
        {
            int jtemp = j;
            while (jtemp > 0 && T[i][C - jtemp].isVide() && !(T[i][C - 1 - jtemp].isVide()))
            {
                T[i][C - jtemp] = T[i][C - 1 - jtemp];
                T[i][C - 1 - jtemp].free();
                jtemp--;
                changement = true;
            }
        }
    }

    // On rajoute une tuile
    if (changement)
        newTile();
}


void plateau::haut()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien, on ne crée pas de nouvelle tuile

    // On supprime les espaces
    for (int j=0; j<C; j++)
    {
        for (int i=1; i<L; i++)
        {
            int itemp = i;
            while (itemp > 0 && T[itemp-1][j].isVide() && !(T[itemp][j].isVide()))
            {
                T[itemp-1][j] = T[itemp][j];
                T[itemp][j].free();
                itemp--;
                changement = true;
            }
        }

    // On effectue ensuite toutes les additions, on pourra rajouter le calcul du score du coup par ici
        for (int i = 0; i<L-1; i++)
        {
            if (T[i][j] == T[i+1][j] && !(T[i][j].isVide()))
            {
                T[i][j].increment();
                T[i+1][j].free();
                changement = true;
            }
        }

    // On va maintenant chercher à supprimer les espaces créés lors des additions
        for (int i=1; i<L; i++)
        {
            int itemp = i;
            while (itemp > 0 && T[itemp-1][j].isVide() && !(T[itemp][j].isVide()))
            {
                T[itemp-1][j] = T[itemp][j];
                T[itemp][j].free();
                itemp--;
                changement = true;
            }
        }
    }

    // On rajoute une tuile
    if (changement)
        newTile();
}


void plateau::bas()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien, on ne crée pas de nouvelle tuile

    for (int j=0; j<C; j++)
    {
        //Mouvement
        for (int i=1; i<L; i++)
        {
            int itemp = i;
            while (itemp > 0 && T[L-itemp][j].isVide() && !(T[L-1-itemp][j].isVide()))
            {
                T[L-itemp][j] = T[L-1-itemp][j];
                T[L-1-itemp][j].free();
                itemp--;
                changement = true;
            }
        }

        //Addition
        for (int i = 0; i<L-1; i++)
        {
            if (T[L-1-i][j] == T[L-2-i][j] && !(T[L-1-i][j].isVide()))
            {
                T[L-2-i][j].increment();
                T[L-1-i][j].free();
                changement = true;
            }
        }

        //Mouvement
        for (int i=1; i<L; i++)
        {
            int itemp = i;
            while (itemp > 0 && T[L-itemp][j].isVide() && !(T[L-1-itemp][j].isVide()))
            {
                T[L-itemp][j] = T[L-1-itemp][j];
                T[L-1-itemp][j].free();
                itemp--;
                changement = true;
            }
        }
    }

    // On rajoute une tuile
    if (changement)
        newTile();
}
