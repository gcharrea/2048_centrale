#ifndef PION_H
#define PION_H

#include <iostream>
using namespace std;

class pion
{
public:
    pion();
    pion& operator= (const pion &p);
    pion& operator+= (const pion &p);
    pion& operator+= (int v);
    pion operator+ (const pion &p);
    void print();

    friend ostream& operator<< (ostream& sortie, DamierExc& V);

private:
    int valeur;
};

#endif // PION_H
