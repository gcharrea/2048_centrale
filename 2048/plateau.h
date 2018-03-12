#ifndef PLATEAU_H
#define PLATEAU_H
#include <QObject>
#include "pion.h"

class plateau : public QObject
{
    Q_OBJECT
public:
    explicit plateau(QObject *parent = nullptr, int l = 4, int c = 4);
private:
    void Alloc(int l, int c);
    int C;
    int L;
    pion** T;
};

#endif // PLATEAU_H
