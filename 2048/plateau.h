#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <fstream>
#include <vector>
#include <QObject>
#include "pion.h"
#include "random.h"


class plateau : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> plateauQML READ readplateauQML NOTIFY plateauQMLChanged)
    Q_PROPERTY(QList<QString> stateQML READ readstateQML NOTIFY stateQMLChanged)


public:
    explicit plateau(int l = 4, int c = 4, QObject *parent = nullptr);

    QList<QString> readplateauQML();
    QList<QString> readstateQML();

    Q_INVOKABLE void gauche();
    Q_INVOKABLE void droite();
    Q_INVOKABLE void haut();
    Q_INVOKABLE void bas();

    Q_INVOKABLE int lignes();
    Q_INVOKABLE int colonnes();
    Q_INVOKABLE int taille();
    Q_INVOKABLE int nbPara();

    int casesVides();
    void newTile();
    Q_INVOKABLE void newGame();

    Q_INVOKABLE void previous();
    Q_INVOKABLE void next();

    Q_INVOKABLE void save(QString filename);
    Q_INVOKABLE void load(QString filename);

private:
    void addCoup(int c);
    void resetHistorique();
    void fakePlay(int c);

private:
    void Alloc(int l, int c);
    int C;
    int L;
    pion** T;
    Random alea;

    bool saveLocked = false;
    int coup = 0;
    vector<int> historique;

signals:
    void plateauQMLChanged();
    void stateQMLChanged();
};

#endif // PLATEAU_H
