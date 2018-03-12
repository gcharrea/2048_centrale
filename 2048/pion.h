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
    Q_INVOKABLE void decrement();

signals:
    void pChanged();
    int readValeur();

public slots:
    
private:
    int Valeur;
};

#endif // PION_H
