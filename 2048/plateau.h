#ifndef PLATEAU_H
#define PLATEAU_H
#include <iostream>
#include <fstream>
#include <vector>
#include <QObject>
#include <string>
#include "pion.h"
#include "random.h"


class plateau : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QString> plateauQML READ readplateauQML NOTIFY plateauQMLChanged)
    Q_PROPERTY(QList<QString> stateQML READ readstateQML NOTIFY stateQMLChanged)
    Q_PROPERTY(QList<QString> deplQML READ readDeplQML NOTIFY animQML)
    //Q_PROPERTY(QList<QString> scoresQML READ readScoreQML NOTIFY signalGameOver)

public:
    explicit plateau(int l = 4, int c = 4, QObject *parent = nullptr);

    QList<QString> readplateauQML();
    QList<QString> readstateQML();
    QList<QString> readDeplQML();

    void initDepl();

    Q_INVOKABLE bool gauche();
    Q_INVOKABLE bool droite();
    Q_INVOKABLE bool haut();
    Q_INVOKABLE bool bas();

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
    Q_INVOKABLE void saveScore();

    Q_INVOKABLE void changeName(int pos, int delta);

    void increaseScore(int v);

private:
    void addCoup(int c);
    void resetHistorique();
    void fakePlay(int c);
    void loadBestScore();

private:
    void Alloc(int l, int c);
    int C;
    int L;
    pion** T;
    Random alea;

    bool saveLocked = false;
    int coup = 0;
    vector<int> historique;
    int score;
    int maxScore;
    int bestScore = 0;

    QString playerName = "AAA";
    QString bestPlayerName = "AAA";

signals:
    void plateauQMLChanged();
    void stateQMLChanged();
    void animQML();
    void signalGameOver();
};

#endif // PLATEAU_H
