#include "plateau.h"

plateau::plateau(int l, int c, QObject *parent) : QObject(parent)
{
    Alloc(l,c);
    emit plateauQMLChanged();
}

void plateau::Alloc(int l, int c)
{
    coup = 0;
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
            Pions.append(T[i][j].readValeur());
    return Pions;
}

QList<QString> plateau::readcolorQML()
{
    QList<QString> Pions;
    QString couleurs[] = {"lightgrey","ghostwhite","beige","lightsalmon","coral",
                          "tomato","orangered","#ffe44d","#ffe033","#ffdd1a",
                          "#f9d406","gold","#42a51c","orchid"};
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            Pions.append(couleurs[T[i][j].valeurPion()%14]);
    return Pions;
}

QList<QString> plateau::readcolorPionQML()
{
    QList<QString> Pions;
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
        {
            if (T[i][j].valeurPion()>2)
            {
                Pions.append(QString("white"));
            }
            else
            {
                Pions.append(QString("black"));
            }
        }
    return Pions;
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

    emit stateQMLChanged();
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

void plateau::gauche()
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
        }

        // On effectue ensuite toutes les additions, on pourra rajouter le calcul du score du
        //coup par ici
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
    if (changement){
        addCoup(0);
        newTile();
    }
}

void plateau::droite()
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
    if (changement){
        addCoup(2);
        newTile();
    }
}

void plateau::bas()
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
    }
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
        fakePlay(historique[coup]);

        saveLocked = false;
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
