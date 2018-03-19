#ifndef PLATEAU_H
#define PLATEAU_H
#include <QObject>
#include "pion.h"

class plateau : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> plateauQML READ readplateauQML NOTIFY plateauQMLChanged)

public:
    explicit plateau(int l = 4, int c = 4, QObject *parent = nullptr);
    QList<QString> readplateauQML();
    Q_INVOKABLE void gauche();
    Q_INVOKABLE void droite();
    Q_INVOKABLE void haut();
    Q_INVOKABLE void bas();
    Q_INVOKABLE int lignes();
    Q_INVOKABLE int colonnes();
    Q_INVOKABLE int taille();
    Q_INVOKABLE void newGame();
    void newTile();
    int casesVides();

private:
    void Alloc(int l, int c);
    int C;
    int L;
    pion** T;

signals:
    void plateauQMLChanged();
};

#endif // PLATEAU_H
