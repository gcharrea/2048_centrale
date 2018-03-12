#include "plateau.h"
#include "pion.h"

plateau::plateau(QObject *parent, int l, int c) : QObject(parent)
{
    Alloc(l,c);
}

void plateau::Alloc(int l, int c)
{
    L = l;
    C = c;
    //T = new pion*[L];
    //for (int i=0; i<L; i++)
    //    T[i] = new pion[C];
}
