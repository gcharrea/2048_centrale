#ifndef PION_H
#define PION_H
#include <QObject>

using namespace std;

class pion : public QObject
{
    Q_OBJECT
public:
    explicit pion(QObject *parent = nullptr);
    void increment();
    QList<QString> readPion();
    int valeurPion();
    bool isVide();
    void free();
    bool operator ==(const pion &p);
    pion& operator =(const pion &p);
    pion& operator =(int v);

    QString Couleur;

public slots:
    
private:
    int Valeur;
    void changeCouleur();
};

#endif // PION_H
