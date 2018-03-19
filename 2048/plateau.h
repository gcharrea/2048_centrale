#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <fstream>
#include <QObject>
#include "pion.h"
#include "random.h"


class plateau : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> plateauQML READ readplateauQML NOTIFY plateauQMLChanged)
    Q_PROPERTY(QList<QString> colorQML READ readcolorQML NOTIFY plateauQMLChanged)

public:
    explicit plateau(int l = 4, int c = 4, QObject *parent = nullptr);
    QList<QString> readplateauQML();
    QList<QString> readcolorQML();
    Q_INVOKABLE void gauche();
    Q_INVOKABLE void droite();
    Q_INVOKABLE void haut();
    Q_INVOKABLE void bas();
    Q_INVOKABLE int lignes();
    Q_INVOKABLE int colonnes();
    Q_INVOKABLE int taille();
    Q_INVOKABLE void newGame();
    Q_INVOKABLE void save(QString filename);
    Q_INVOKABLE void load(QString filename);
    void newTile();
    int casesVides();

private:
    void Alloc(int l, int c);
    int C;
    int L;
    pion** T;
    Random alea;


signals:
    void plateauQMLChanged();
};

#endif // PLATEAU_H
