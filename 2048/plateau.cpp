#include "plateau.h"
#include <cmath>

plateau::plateau(int l, int c, QObject *parent) : QObject(parent)
{
    Alloc(l,c);
    emit plateauQMLChanged();
}

void plateau::Alloc(int l, int c)
{
    resetHistorique();
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
            Pions.append(T[i][j].readPion());
    return Pions;
}

int plateau::nbPara(){
    return 3;
}

QList<QString> plateau::readstateQML(){
    QList<QString> states;
    QString sCoup = QString::number(coup);
    if(coup != (int) historique.size()){
        sCoup.append("/");
        sCoup.append(QString::number(historique.size()));
    }
    states.append(sCoup);
    states.append(QString::number(historique.size()));

    QString sScore = "Score : " + QString::number(score);
    if(score != maxScore){
        sScore.append("/");
        sScore.append(QString::number(maxScore));
    }
    states.append(sScore);
    return states;
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

    emit stateQMLChanged();


    if(c==1 && !saveLocked){
        saveLocked = true;
        this->blockSignals(true);

        if(gauche()){
            coup++;
            previous();
        }else if(droite()){
            coup++;
            previous();
        }else if(haut()){
            coup++;
            previous();
        }else if(bas()){
            coup++;
            previous();
        }else{
            std::cout << "game over" << std::endl;
        }

        this->blockSignals(false);
        saveLocked = false;
    }
}

void plateau::newGame()
{
    if(!saveLocked)
        alea = Random();
    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
            T[i][j].free();
    resetHistorique();
    newTile();
}

bool plateau::gauche()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien, on ne
    //crée pas de nouvelle tuile

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

            if (jtemp != j)
            {
                T[i][j].depl = "gauche";
                T[i][j].nb = j-jtemp;
            }
        }
        emit animQML();
        initDepl();

        // On effectue ensuite toutes les additions, on pourra rajouter le calcul du score du
        //coup par ici
        for (int j = 0; j<C-1; j++)
        {
            if (T[i][j] == T[i][j+1] && !(T[i][j].isVide()))
            {
                T[i][j].increment();
                T[i][j+1].free();
                this->increaseScore(T[i][j].valeurPion());
                changement = true;

                T[i][j+1].depl = "gauche";
                T[i][j+1].nb = 1;
            }
        }
        emit animQML();
        initDepl();

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

            if (jtemp != j)
            {
                T[i][j].depl = "gauche";
                T[i][j].nb = j-jtemp;
            }
        }
        emit animQML();
        initDepl();
    }

    // On rajoute une tuile
    if (changement){
        addCoup(0);
        newTile();
    }
    return changement;
}

bool plateau::droite()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien,
    //on ne crée pas de nouvelle tuile

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
                T[i][C-1-j].increment();
                this->increaseScore(T[i][C-1-j].valeurPion());
                T[i][C-2-j].free();
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
    if (changement){
        addCoup(1);
        newTile();
    }
    return changement;
}

bool plateau::haut()
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
                this->increaseScore(T[i][j].valeurPion());
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
    if (changement){
        addCoup(2);
        newTile();
    }
    return changement;
}

bool plateau::bas()
{
    bool changement = false;
    // Ce booléen vérifie si le coup fait quelque chose, s'il ne fait rien,
    //on ne crée pas de nouvelle tuile

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
                T[L-1-i][j].increment();
                this->increaseScore(T[L-1-i][j].valeurPion());
                T[L-2-i][j].free();
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
    if (changement){
        addCoup(3);
        newTile();
    }
    return changement;
}

void plateau::addCoup(int c){
    if(!saveLocked){
        if(coup < (int) historique.size()){
            historique.resize(coup);
        }
        coup++;
        historique.push_back(c);
    }
}

void plateau::resetHistorique(){
    if(!saveLocked){
        coup = 0;
        historique.clear();
        maxScore = 0;
    }
    score = 0;
}

void plateau::fakePlay(int c){
    switch (c) {
    case 0:
        gauche();
        break;
    case 1:
        droite();
        break;
    case 2:
        haut();
        break;
    case 3:
        bas();
        break;
    default:
        break;
    }
}

void plateau::previous(){
    if(coup > 0){
        saveLocked = true;

        coup--;
        alea.reset();
        newGame();
        for(int i = 0; i < coup; i++){
            fakePlay(historique[i]);
        }

        saveLocked = false;
    }
}

void plateau::next(){
    if(coup < (int) historique.size()){
        saveLocked = true;

        coup++;
        fakePlay(historique[coup-1]);

        saveLocked = false;
    }
}

void plateau::increaseScore(int v){
    score += pow(2, v);
    if(!saveLocked){
        maxScore = score;
    }
}

void plateau::save(QString filename){
    filename.remove("file://");
    if(!filename.contains('.'))
        filename.append(".2k8");

    cout << "save at : " << filename.toStdString() << endl;
    ofstream save;
    save.open(filename.toStdString());
    save << alea << endl;
    save << L << " " << C << endl;
    for (int i=0; i<L; i++){
        for (int j=0; j<C; j++){
         save << T[i][j].valeurPion() << " ";
        }
        save << endl;
    }
    save << coup << endl;
    for(int c : historique){
        save << c << " ";
    }
    save.close();
}

void plateau::load(QString filename){
    ifstream save;
    filename.remove("file://");
    cout << "load : " << filename.toStdString() << endl;
    save.open(filename.toStdString());
    save >> alea;
    save >> L;
    save >> C;
    Alloc(L, C);
    int v;
    for (int i=0; i<L; i++){
        for (int j=0; j<C; j++){
         save >> v;
         T[i][j] = v;
        }
    }
    save >> coup;
    historique = vector<int>();
    for(int i = 0; i < coup; i++){
        save >> v;
        historique.push_back(v);
    }
    save.close();
    emit plateauQMLChanged();
}

void plateau::initDepl(){
    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
        {
            T[i][j].depl = "";
            T[i][j].nb = 0;
        }
}

QList<QString> plateau::readDeplQML(){
    QList<QString> depl;

    for (int i=0; i<L; i++)
        for (int j=0; j<C; j++)
        {
            depl.append(T[i][j].depl);
            depl.append(QString::number(T[i][j].nb));
        }

    return depl;
}
