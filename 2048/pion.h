#ifndef PION_H
#define PION_H
#include <QObject>

using namespace std;

class pion : public QObject
{
    Q_OBJECT
public:
    explicit pion(QObject *parent = nullptr);
    Q_INVOKABLE void increment();
    QString readValeur();
    int valeurPion();
    bool isVide();
    void free();
    bool operator ==(const pion &p);
    pion& operator =(const pion &p);
    pion& operator =(int v);


signals:
    void pChanged();

public slots:
    
private:
    int Valeur;
};

#endif // PION_H
